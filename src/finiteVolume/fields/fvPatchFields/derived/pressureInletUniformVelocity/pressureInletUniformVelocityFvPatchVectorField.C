/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011 OpenFOAM Foundation
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

#include "fields/fvPatchFields/derived/pressureInletUniformVelocity/pressureInletUniformVelocityFvPatchVectorField.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"
#include "fields/volFields/volFields.H"
#include "fields/surfaceFields/surfaceFields.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::pressureInletUniformVelocityFvPatchVectorField::
pressureInletUniformVelocityFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
    pressureInletVelocityFvPatchVectorField(p, iF)
{}


Foam::pressureInletUniformVelocityFvPatchVectorField::
pressureInletUniformVelocityFvPatchVectorField
(
    const pressureInletUniformVelocityFvPatchVectorField& ptf,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    pressureInletVelocityFvPatchVectorField(ptf, p, iF, mapper)
{}


Foam::pressureInletUniformVelocityFvPatchVectorField::
pressureInletUniformVelocityFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
:
    pressureInletVelocityFvPatchVectorField(p, iF, dict)
{}


Foam::pressureInletUniformVelocityFvPatchVectorField::
pressureInletUniformVelocityFvPatchVectorField
(
    const pressureInletUniformVelocityFvPatchVectorField& pivpvf
)
:
    pressureInletVelocityFvPatchVectorField(pivpvf)
{}


Foam::pressureInletUniformVelocityFvPatchVectorField::
pressureInletUniformVelocityFvPatchVectorField
(
    const pressureInletUniformVelocityFvPatchVectorField& pivpvf,
    const DimensionedField<vector, volMesh>& iF
)
:
    pressureInletVelocityFvPatchVectorField(pivpvf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::pressureInletUniformVelocityFvPatchVectorField::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    pressureInletVelocityFvPatchVectorField::updateCoeffs();

    operator==(patch().nf()*gSum(patch().Sf() & *this)/gSum(patch().magSf()));
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void Foam::pressureInletUniformVelocityFvPatchVectorField::operator=
(
    const fvPatchField<vector>& pvf
)
{
    operator==(patch().nf()*gSum(patch().Sf() & pvf)/gSum(patch().magSf()));
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    makePatchTypeField
    (
        fvPatchVectorField,
        pressureInletUniformVelocityFvPatchVectorField
    );
}

// ************************************************************************* //
