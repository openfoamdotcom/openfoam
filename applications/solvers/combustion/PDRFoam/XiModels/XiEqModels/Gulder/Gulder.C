/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
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

#include "XiModels/XiEqModels/Gulder/Gulder.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace XiEqModels
{
    defineTypeNameAndDebug(Gulder, 0);
    addToRunTimeSelectionTable(XiEqModel, Gulder, dictionary);
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::XiEqModels::Gulder::Gulder
(
    const dictionary& XiEqProperties,
    const psiuReactionThermo& thermo,
    const compressible::RASModel& turbulence,
    const volScalarField& Su
)
:
    XiEqModel(XiEqProperties, thermo, turbulence, Su),
    XiEqCoef_(XiEqModelCoeffs_.get<scalar>("XiEqCoef")),
    SuMin_(0.01*Su.average()),
    uPrimeCoef_(XiEqModelCoeffs_.get<scalar>("uPrimeCoef")),
    subGridSchelkin_(XiEqModelCoeffs_.get<bool>("subGridSchelkin"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::XiEqModels::Gulder::~Gulder()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Foam::tmp<Foam::volScalarField> Foam::XiEqModels::Gulder::XiEq() const
{
    volScalarField up(sqrt((2.0/3.0)*turbulence_.k()));
    const volScalarField& epsilon = turbulence_.epsilon();

    if (subGridSchelkin_)
    {
        up.primitiveFieldRef() += calculateSchelkinEffect(uPrimeCoef_);
    }

    volScalarField tauEta(sqrt(mag(thermo_.muu()/(thermo_.rhou()*epsilon))));

    volScalarField Reta
    (
        up
      / (
            sqrt(epsilon*tauEta)
          + dimensionedScalar("1e-8", up.dimensions(), 1e-8)
        )
    );

    return (1.0 + XiEqCoef_*sqrt(up/(Su_ + SuMin_))*Reta);
}


bool Foam::XiEqModels::Gulder::read(const dictionary& XiEqProperties)
{
    XiEqModel::read(XiEqProperties);

    XiEqModelCoeffs_.readEntry("XiEqCoef", XiEqCoef_);
    XiEqModelCoeffs_.readEntry("uPrimeCoef", uPrimeCoef_);
    XiEqModelCoeffs_.readEntry("subGridSchelkin", subGridSchelkin_);

    return true;
}


// ************************************************************************* //
