/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
    Copyright (C) 2023 OpenCFD Ltd.
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
    Foam::processorCyclicPointPatchField

Description
    Foam::processorCyclicPointPatchField

SourceFiles
    processorCyclicPointPatchField.C

\*---------------------------------------------------------------------------*/

#ifndef Foam_processorCyclicPointPatchField_H
#define Foam_processorCyclicPointPatchField_H

#include "fields/pointPatchFields/basic/coupled/coupledPointPatchField.H"
#include "meshes/pointMesh/pointPatches/constraint/processorCyclic/processorCyclicPointPatch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                 Class processorCyclicPointPatchField Declaration
\*---------------------------------------------------------------------------*/

template<class Type>
class processorCyclicPointPatchField
:
    public coupledPointPatchField<Type>
{
    // Private Data

        //- Local reference to processor patch
        const processorCyclicPointPatch& procPatch_;

        //- Send buffer for non-blocking communication
        mutable Field<Type> sendBuf_;

        //- Receive buffer for non-blocking communication
        mutable Field<Type> recvBuf_;


public:

    //- Runtime type information
    TypeName(processorCyclicPointPatch::typeName_());


    // Constructors

        //- Construct from patch and internal field
        processorCyclicPointPatchField
        (
            const pointPatch&,
            const DimensionedField<Type, pointMesh>&
        );

        //- Construct from patch, internal field and dictionary
        processorCyclicPointPatchField
        (
            const pointPatch&,
            const DimensionedField<Type, pointMesh>&,
            const dictionary&
        );

        //- Construct by mapping given patch field onto a new patch
        processorCyclicPointPatchField
        (
            const processorCyclicPointPatchField<Type>&,
            const pointPatch&,
            const DimensionedField<Type, pointMesh>&,
            const pointPatchFieldMapper&
        );

        //- Construct and return a clone
        virtual autoPtr<pointPatchField<Type>> clone() const
        {
            return autoPtr<pointPatchField<Type>>
            (
                new processorCyclicPointPatchField<Type>
                (
                    *this
                )
            );
        }

        //- Construct as copy setting internal field reference
        processorCyclicPointPatchField
        (
            const processorCyclicPointPatchField<Type>&,
            const DimensionedField<Type, pointMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual autoPtr<pointPatchField<Type>> clone
        (
            const DimensionedField<Type, pointMesh>& iF
        ) const
        {
            return autoPtr<pointPatchField<Type>>
            (
                new processorCyclicPointPatchField<Type>
                (
                    *this,
                    iF
                )
            );
        }


    //- Destructor
    virtual ~processorCyclicPointPatchField() = default;


    // Member functions

        // Access

            //- Return true if running parallel
            virtual bool coupled() const
            {
                return Pstream::parRun();
            }

            //- Does the patch field perform the transformation
            virtual bool doTransform() const
            {
                return
                (
                    pTraits<Type>::rank
                 && !procPatch_.procPolyPatch().parallel()
                );
            }


        // Evaluation functions

            //- Evaluate the patch field
            virtual void evaluate
            (
                const Pstream::commsTypes commsType =
                    Pstream::commsTypes::blocking
            )
            {}

            //- Initialise swap of non-collocated patch point values
            virtual void initSwapAddSeparated
            (
                const Pstream::commsTypes commsType,
                Field<Type>&
            ) const;

            //- Complete swap of patch point values and add to local values
            virtual void swapAddSeparated
            (
                const Pstream::commsTypes commsType,
                Field<Type>&
            ) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "fields/pointPatchFields/constraint/processorCyclic/processorCyclicPointPatchField.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
