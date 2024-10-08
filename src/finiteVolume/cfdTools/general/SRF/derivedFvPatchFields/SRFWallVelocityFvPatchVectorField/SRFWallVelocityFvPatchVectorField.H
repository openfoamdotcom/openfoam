/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016 OpenFOAM Foundation
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

Class
    Foam::SRFWallVelocityFvPatchVectorField

Group
    grpWallBoundaryConditions

Description
    Wall-velocity condition to be used in conjunction with the single rotating
    frame (SRF) model (see: FOAM::SRFModel)

    The condition applies the appropriate rotation transformation in time and
    space to determine the local SRF velocity of the wall.

        \f[
            U_p = - U_{p,srf}
        \f]

    where
    \vartable
        U_p     = patch velocity [m/s]
        U_{p,srf} = SRF velocity
    \endvartable

    The normal component of \f$ U_p \f$ is removed to ensure 0 wall-flux even
    if the wall patch faces are irregular.

Usage
    Example of the boundary condition specification:
    \verbatim
    <patchName>
    {
        type            SRFWallVelocity;
        value           uniform (0 0 0);    // Initial value
    }
    \endverbatim

See also
    Foam::SRFModel
    Foam::SRFVelocityFvPatchVectorField
    Foam::fixedValueFvPatchField

SourceFiles
    SRFWallVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#ifndef SRFWallVelocityFvPatchVectorField_H
#define SRFWallVelocityFvPatchVectorField_H

#include "fields/fvPatchFields/fvPatchField/fvPatchFields.H"
#include "fields/fvPatchFields/basic/fixedValue/fixedValueFvPatchFields.H"
#include "primitives/bools/Switch/Switch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
               Class SRFWallVelocityFvPatchVectorField Declaration
\*---------------------------------------------------------------------------*/

class SRFWallVelocityFvPatchVectorField
:
    public fixedValueFvPatchVectorField
{

public:

    //- Runtime type information
    TypeName("SRFWallVelocity");


    // Constructors

        //- Construct from patch and internal field
        SRFWallVelocityFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        SRFWallVelocityFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given SRFWallVelocityFvPatchVectorField
        //  onto a new patch
        SRFWallVelocityFvPatchVectorField
        (
            const SRFWallVelocityFvPatchVectorField&,
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        SRFWallVelocityFvPatchVectorField
        (
            const SRFWallVelocityFvPatchVectorField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchVectorField> clone() const
        {
            return tmp<fvPatchVectorField>
            (
                new SRFWallVelocityFvPatchVectorField(*this)
            );
        }

        //- Construct as copy setting internal field reference
        SRFWallVelocityFvPatchVectorField
        (
            const SRFWallVelocityFvPatchVectorField&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchVectorField> clone
        (
            const DimensionedField<vector, volMesh>& iF
        ) const
        {
            return tmp<fvPatchVectorField>
            (
                new SRFWallVelocityFvPatchVectorField(*this, iF)
            );
        }


    // Member functions

        // Mapping functions

            //- Map (and resize as needed) from self given a mapping object
            virtual void autoMap
            (
                const fvPatchFieldMapper&
            );

            //- Reverse map the given fvPatchField onto this fvPatchField
            virtual void rmap
            (
                const fvPatchVectorField&,
                const labelList&
            );


        // Evaluation functions

            //- Update the coefficients associated with the patch field
            virtual void updateCoeffs();


        // I-O

            //- Write
            virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
