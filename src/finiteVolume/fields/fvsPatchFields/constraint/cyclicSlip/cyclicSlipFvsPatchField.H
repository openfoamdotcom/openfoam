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

Class
    Foam::cyclicSlipFvsPatchField

Description
    Foam::cyclicSlipFvsPatchField

SourceFiles
    cyclicSlipFvsPatchField.C

\*---------------------------------------------------------------------------*/

#ifndef cyclicSlipFvsPatchField_H
#define cyclicSlipFvsPatchField_H

#include "fields/fvsPatchFields/constraint/cyclic/cyclicFvsPatchField.H"
#include "fvMesh/fvPatches/constraint/cyclicSlip/cyclicSlipFvPatch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class cyclicSlipFvsPatch Declaration
\*---------------------------------------------------------------------------*/

template<class Type>
class cyclicSlipFvsPatchField
:
    public cyclicFvsPatchField<Type>
{

public:

    //- Runtime type information
    TypeName(cyclicSlipFvPatch::typeName_());


    // Constructors

        //- Construct from patch and internal field
        cyclicSlipFvsPatchField
        (
            const fvPatch&,
            const DimensionedField<Type, surfaceMesh>&
        );

        //- Construct from patch, internal field and dictionary
        cyclicSlipFvsPatchField
        (
            const fvPatch&,
            const DimensionedField<Type, surfaceMesh>&,
            const dictionary&
        );

        //- Construct by mapping given cyclicSlipFvsPatchField onto a new patch
        cyclicSlipFvsPatchField
        (
            const cyclicSlipFvsPatchField<Type>&,
            const fvPatch&,
            const DimensionedField<Type, surfaceMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        cyclicSlipFvsPatchField
        (
            const cyclicSlipFvsPatchField<Type>&
        );

        //- Construct and return a clone
        virtual tmp<fvsPatchField<Type>> clone() const
        {
            return tmp<fvsPatchField<Type>>
            (
                new cyclicSlipFvsPatchField<Type>(*this)
            );
        }

        //- Construct as copy setting internal field reference
        cyclicSlipFvsPatchField
        (
            const cyclicSlipFvsPatchField<Type>&,
            const DimensionedField<Type, surfaceMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvsPatchField<Type>> clone
        (
            const DimensionedField<Type, surfaceMesh>& iF
        ) const
        {
            return tmp<fvsPatchField<Type>>
            (
                new cyclicSlipFvsPatchField<Type>(*this, iF)
            );
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "fields/fvsPatchFields/constraint/cyclicSlip/cyclicSlipFvsPatchField.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
