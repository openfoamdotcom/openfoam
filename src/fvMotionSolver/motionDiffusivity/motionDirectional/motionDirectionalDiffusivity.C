/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2012 OpenFOAM Foundation
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

#include "motionDiffusivity/motionDirectional/motionDirectionalDiffusivity.H"
#include "interpolation/surfaceInterpolation/surfaceInterpolation/surfaceInterpolate.H"
#include "fields/fvPatchFields/basic/zeroGradient/zeroGradientFvPatchFields.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"
#include "motionSolvers/velocity/velocityMotionSolver.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(motionDirectionalDiffusivity, 0);

    addToRunTimeSelectionTable
    (
        motionDiffusivity,
        motionDirectionalDiffusivity,
        Istream
    );
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::motionDirectionalDiffusivity::motionDirectionalDiffusivity
(
    const fvMesh& mesh,
    Istream& mdData
)
:
    uniformDiffusivity(mesh, mdData),
    diffusivityVector_(mdData)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::motionDirectionalDiffusivity::~motionDirectionalDiffusivity()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::motionDirectionalDiffusivity::correct()
{
    static bool first = true;

    if (!first)
    {
        const volVectorField& cellMotionU =
            mesh().lookupObject<volVectorField>("cellMotionU");

        volVectorField D
        (
            IOobject
            (
                "D",
                mesh().time().timeName(),
                mesh()
            ),
            diffusivityVector_.y()*vector::one
          + (diffusivityVector_.x() - diffusivityVector_.y())*cellMotionU
           /(mag(cellMotionU) + dimensionedScalar("small", dimVelocity, SMALL)),

            fvPatchFieldBase::zeroGradientType()
        );
        D.correctBoundaryConditions();

        const surfaceVectorField n(mesh().Sf()/mesh().magSf());
        faceDiffusivity_ == (n & cmptMultiply(fvc::interpolate(D), n));
    }
    else
    {
        first = false;

        const velocityMotionSolver& mSolver =
            mesh().lookupObject<velocityMotionSolver>("dynamicMeshDict");

        const_cast<velocityMotionSolver&>(mSolver).solve();
        correct();
    }
}


// ************************************************************************* //
