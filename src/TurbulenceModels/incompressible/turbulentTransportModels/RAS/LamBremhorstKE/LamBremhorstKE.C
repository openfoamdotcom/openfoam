/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
    Copyright (C) 2019-2020,2023 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "turbulentTransportModels/RAS/LamBremhorstKE/LamBremhorstKE.H"
#include "fvMesh/wallDist/wallDist/wallDist.H"
#include "cfdTools/general/bound/bound.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace incompressible
{
namespace RASModels
{

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(LamBremhorstKE, 0);
addToRunTimeSelectionTable(RASModel, LamBremhorstKE, dictionary);

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

tmp<volScalarField> LamBremhorstKE::Rt() const
{
    return sqr(k_)/(nu()*epsilon_);
}


tmp<volScalarField> LamBremhorstKE::fMu(const volScalarField& Rt) const
{
    tmp<volScalarField> Ry(sqrt(k_)*y_/nu());
    return sqr(scalar(1) - exp(-0.0165*Ry))*(scalar(1) + 20.5/(Rt + SMALL));
}


tmp<volScalarField> LamBremhorstKE::f1(const volScalarField& fMu) const
{
    return scalar(1) + pow3(0.05/(fMu + SMALL));
}


tmp<volScalarField> LamBremhorstKE::f2(const volScalarField& Rt) const
{
    return scalar(1) - exp(-sqr(Rt));
}


void LamBremhorstKE::correctNut(const volScalarField& fMu)
{
    nut_ = Cmu_*fMu*sqr(k_)/epsilon_;
    nut_.correctBoundaryConditions();
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void LamBremhorstKE::correctNut()
{
    correctNut(fMu(Rt()));
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

LamBremhorstKE::LamBremhorstKE
(
    const geometricOneField& alpha,
    const geometricOneField& rho,
    const volVectorField& U,
    const surfaceScalarField& alphaRhoPhi,
    const surfaceScalarField& phi,
    const transportModel& transport,
    const word& propertiesName,
    const word& type
)
:
    eddyViscosity<incompressible::RASModel>
    (
        type,
        alpha,
        rho,
        U,
        alphaRhoPhi,
        phi,
        transport,
        propertiesName
    ),

    Cmu_
    (
        dimensioned<scalar>::getOrAddToDict
        (
            "Cmu",
            coeffDict_,
            0.09
        )
    ),
    Ceps1_
    (
        dimensioned<scalar>::getOrAddToDict
        (
            "Ceps1",
            coeffDict_,
            1.44
        )
    ),
    Ceps2_
    (
        dimensioned<scalar>::getOrAddToDict
        (
            "Ceps2",
            coeffDict_,
            1.92
        )
    ),
    sigmaEps_
    (
        dimensioned<scalar>::getOrAddToDict
        (
            "alphaEps",
            coeffDict_,
            1.3
        )
    ),

    k_
    (
        IOobject
        (
            IOobject::groupName("k", alphaRhoPhi.group()),
            runTime_.timeName(),
            mesh_,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh_
    ),

    epsilon_
    (
        IOobject
        (
            IOobject::groupName("epsilon", alphaRhoPhi.group()),
            runTime_.timeName(),
            mesh_,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh_
    ),

    y_(wallDist::New(mesh_).y())
{
    bound(k_, kMin_);
    bound(epsilon_, epsilonMin_);

    if (type == typeName)
    {
        printCoeffs(type);
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool LamBremhorstKE::read()
{
    if (eddyViscosity<incompressible::RASModel>::read())
    {
        Cmu_.readIfPresent(coeffDict());
        Ceps1_.readIfPresent(coeffDict());
        Ceps2_.readIfPresent(coeffDict());
        sigmaEps_.readIfPresent(coeffDict());

        return true;
    }

    return false;
}


void LamBremhorstKE::correct()
{
    if (!turbulence_)
    {
        return;
    }

    eddyViscosity<incompressible::RASModel>::correct();

    tmp<volTensorField> tgradU = fvc::grad(U_);
    volScalarField G(GName(), nut_*(twoSymm(tgradU()) && tgradU()));
    tgradU.clear();

    // Update epsilon and G at the wall
    epsilon_.boundaryFieldRef().updateCoeffs();
    // Push any changed cell values to coupled neighbours
    epsilon_.boundaryFieldRef().evaluateCoupled<coupledFvPatch>();

    const volScalarField Rt(this->Rt());
    const volScalarField fMu(this->fMu(Rt));

    // Dissipation equation
    tmp<fvScalarMatrix> epsEqn
    (
        fvm::ddt(epsilon_)
      + fvm::div(phi_, epsilon_)
      - fvm::laplacian(DepsilonEff(), epsilon_)
     ==
        Ceps1_*f1(fMu)*G*epsilon_/k_
      - fvm::Sp(Ceps2_*f2(Rt)*epsilon_/k_, epsilon_)
    );

    epsEqn.ref().relax();
    epsEqn.ref().boundaryManipulate(epsilon_.boundaryFieldRef());
    solve(epsEqn);
    bound(epsilon_, epsilonMin_);

    // Turbulent kinetic energy equation
    tmp<fvScalarMatrix> kEqn
    (
        fvm::ddt(k_)
      + fvm::div(phi_, k_)
      - fvm::laplacian(DkEff(), k_)
     ==
        G - fvm::Sp(epsilon_/k_, k_)
    );

    kEqn.ref().relax();
    solve(kEqn);
    bound(k_, kMin_);

    // Update nut with latest available k,epsilon
    correctNut();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace RASModels
} // End namespace incompressible
} // End namespace Foam

// ************************************************************************* //
