/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016-2017 Wikki Ltd
    Copyright (C) 2019-2023 OpenCFD Ltd.
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
    Foam::faPatchField

Description
    faPatchField<Type> abstract base class.  This class gives a fat-interface
    to all derived classes covering all possible ways in which they might be
    used.  The first level of derivation is to basic patchFields which cover
    zero-gradient, fixed-gradient, fixed-value and mixed conditions.  The next
    level of derivation covers all the specialised typed with specific
    evaluation procedures, particularly with respect to specific fields.

Author
    Zeljko Tukovic, FMENA
    Hrvoje Jasak, Wikki Ltd.

SourceFiles
    faPatchField.C
    faPatchFieldBase.C
    faPatchFieldNew.C

\*---------------------------------------------------------------------------*/

#ifndef Foam_faPatchField_H
#define Foam_faPatchField_H

#include "faMesh/faPatches/faPatch/faPatch.H"
#include "fields/DimensionedFields/DimensionedField/DimensionedField.H"
#include "fields/Fields/fieldTypes.H"
#include "fields/Fields/scalarField/scalarField.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward Declarations
class dictionary;
class objectRegistry;
class faPatchFieldMapper;
class areaMesh;

template<class Type> class faPatchField;
template<class Type> class calculatedFaPatchField;
template<class Type> class zeroGradientFaPatchField;

template<class Type>
Ostream& operator<<(Ostream&, const faPatchField<Type>&);

/*---------------------------------------------------------------------------*\
                      Class faPatchFieldBase Declaration
\*---------------------------------------------------------------------------*/

//- Template invariant parts for faPatchField
class faPatchFieldBase
{
    // Private Data

        //- Reference to patch
        const faPatch& patch_;

        //- Update index used so that updateCoeffs is called only once during
        //- the construction of the matrix
        bool updated_;

        //- Optional patch type
        //  Used to allow specified boundary conditions to be applied
        //  to constraint patches by providing the constraint
        //  patch type as 'patchType'
        word patchType_;


protected:

    // Protected Member Functions

        //- Read dictionary entries.
        //  Useful when initially constructed without a dictionary
        virtual void readDict(const dictionary& dict);


public:

    //- Debug switch to disallow the use of generic faPatchField
    static int disallowGenericPatchField;

    //- Runtime type information
    TypeName("faPatchField");


    // Constructors

        //- Construct from patch
        explicit faPatchFieldBase(const faPatch& p);

        //- Construct from patch and patch type
        explicit faPatchFieldBase(const faPatch& p, const word& patchType);

        //- Construct from patch and dictionary
        faPatchFieldBase(const faPatch& p, const dictionary& dict);

        //- Copy construct with new patch
        faPatchFieldBase(const faPatchFieldBase& rhs, const faPatch& p);

        //- Copy construct
        faPatchFieldBase(const faPatchFieldBase& rhs);


    //- Destructor
    virtual ~faPatchFieldBase() = default;


    // Static Member Functions

        //- The type name for \c empty patch fields
        static const word& emptyType() noexcept
        {
            return Foam::fieldTypes::emptyType;
        }

        //- The type name for \c calculated patch fields
        static const word& calculatedType() noexcept
        {
            return Foam::fieldTypes::calculatedType;
        }

        //- The type name for \c extrapolatedCalculated patch fields
        //- combines \c zero-gradient and \c calculated
        static const word& extrapolatedCalculatedType() noexcept
        {
            return Foam::fieldTypes::extrapolatedCalculatedType;
        }

        //- The type name for \c zeroGradient patch fields
        static const word& zeroGradientType() noexcept
        {
            return Foam::fieldTypes::zeroGradientType;
        }


    // Member Functions

    // Attributes

        //- True if the patch field fixes a value.
        //  Needed to check if a level has to be specified while solving
        //  Poissons equations.
        virtual bool fixesValue() const
        {
            return false;
        }

        //- True if the patch field is coupled
        virtual bool coupled() const
        {
            return false;
        }


    // Access

        //- The associated objectRegistry
        const objectRegistry& db() const;

        //- Return the patch
        const faPatch& patch() const noexcept
        {
            return patch_;
        }

        //- The optional patch type
        const word& patchType() const noexcept
        {
            return patchType_;
        }

        //- The optional patch type
        word& patchType() noexcept
        {
            return patchType_;
        }


    // Solution

        //- True if the boundary condition has already been updated
        bool updated() const noexcept
        {
            return updated_;
        }

        //- Set updated state
        void setUpdated(bool state) noexcept
        {
            updated_ = state;
        }


    // Check

        //- Check that patches are identical
        void checkPatch(const faPatchFieldBase& rhs) const;
};


/*---------------------------------------------------------------------------*\
                        Class faPatchField Declaration
\*---------------------------------------------------------------------------*/

template<class Type>
class faPatchField
:
    public faPatchFieldBase,
    public Field<Type>
{
    // Private Data

        //- Reference to internal field
        const DimensionedField<Type, areaMesh>& internalField_;

protected:

    // Protected Member Functions

        //- Read the "value" entry into \c *this.
        //  The reading can be optional (default), mandatory etc.
        //  \returns True on success
        bool readValueEntry
        (
            const dictionary& dict,
            IOobjectOption::readOption readOpt = IOobjectOption::LAZY_READ
        );

        //- Write *this field as a "value" entry
        void writeValueEntry(Ostream& os) const
        {
            Field<Type>::writeEntry("value", os);
        }

        //- Assign the patch field from the internal field
        void extrapolateInternal();


public:

    //- The internal field type associated with the patch field
    typedef DimensionedField<Type, areaMesh> Internal;

    //- The patch type for the patch field
    typedef faPatch Patch;

    //- Type for a \em calculated patch
    typedef calculatedFaPatchField<Type> Calculated;


    // Declare run-time constructor selection tables

        declareRunTimeSelectionTable
        (
            tmp,
            faPatchField,
            patch,
            (
                const faPatch& p,
                const DimensionedField<Type, areaMesh>& iF
            ),
            (p, iF)
        );

        declareRunTimeSelectionTable
        (
            tmp,
            faPatchField,
            patchMapper,
            (
                const faPatchField<Type>& ptf,
                const faPatch& p,
                const DimensionedField<Type, areaMesh>& iF,
                const faPatchFieldMapper& m
            ),
            (dynamic_cast<const faPatchFieldType&>(ptf), p, iF, m)
        );

        declareRunTimeSelectionTable
        (
            tmp,
            faPatchField,
            dictionary,
            (
                const faPatch& p,
                const DimensionedField<Type, areaMesh>& iF,
                const dictionary& dict
            ),
            (p, iF, dict)
        );


    // Constructors

        //- Construct from patch and internal field
        faPatchField
        (
            const faPatch&,
            const DimensionedField<Type, areaMesh>&
        );

        //- Construct from patch, internal field and value
        faPatchField
        (
            const faPatch&,
            const DimensionedField<Type, areaMesh>&,
            const Type& value
        );

        //- Construct from patch, internal field and patch field
        faPatchField
        (
            const faPatch&,
            const DimensionedField<Type, areaMesh>&,
            const Field<Type>& pfld
        );

        //- Construct from patch, internal field and patch field
        faPatchField
        (
            const faPatch&,
            const DimensionedField<Type, areaMesh>&,
            Field<Type>&& pfld
        );

        //- Construct from patch, internal field and dictionary.
        //  \note older versions have always treated "value" as optional
        faPatchField
        (
            const faPatch&,
            const DimensionedField<Type, areaMesh>&,
            const dictionary& dict,
            //! The "value" entry (default: optional)
            IOobjectOption::readOption requireValue = IOobjectOption::LAZY_READ
        );

        //- Construct by mapping the given faPatchField onto a new patch
        faPatchField
        (
            const faPatchField<Type>&,
            const faPatch&,
            const DimensionedField<Type, areaMesh>&,
            const faPatchFieldMapper&
        );

        //- Construct as copy
        faPatchField(const faPatchField<Type>&);

        //- Construct as copy setting internal field reference
        faPatchField
        (
            const faPatchField<Type>&,
            const DimensionedField<Type, areaMesh>&
        );

        //- Construct and return a clone
        virtual tmp<faPatchField<Type>> clone() const
        {
            return tmp<faPatchField<Type>>(new faPatchField<Type>(*this));
        }

        //- Construct and return a clone setting internal field reference
        virtual tmp<faPatchField<Type>> clone
        (
            const DimensionedField<Type, areaMesh>& iF
        ) const
        {
            return tmp<faPatchField<Type>>(new faPatchField<Type>(*this, iF));
        }


    // Selectors

        //- Return a pointer to a new patchField created on freestore given
        //- patch and internal field
        //  (does not set the patch field values)
        static tmp<faPatchField<Type>> New
        (
            const word& patchFieldType,
            const word& actualPatchType,
            const faPatch&,
            const DimensionedField<Type, areaMesh>&
        );

        //- Return a pointer to a new patchField created on freestore given
        //- patch and internal field
        //  (does not set the patch field values)
        static tmp<faPatchField<Type>> New
        (
            const word& patchFieldType,
            const faPatch&,
            const DimensionedField<Type, areaMesh>&
        );

        //- Return a pointer to a new patchField created on freestore from
        //- a given faPatchField mapped onto a new patch
        static tmp<faPatchField<Type>> New
        (
            const faPatchField<Type>&,
            const faPatch&,
            const DimensionedField<Type, areaMesh>&,
            const faPatchFieldMapper&
        );

        //- Return a pointer to a new patchField created on freestore
        //- from dictionary
        static tmp<faPatchField<Type>> New
        (
            const faPatch&,
            const DimensionedField<Type, areaMesh>&,
            const dictionary&
        );

        //- Return a pointer to a new calculatedFaPatchField created on
        //- freestore without setting patchField values
        template<class AnyType>
        static tmp<faPatchField<Type>> NewCalculatedType
        (
            const faPatchField<AnyType>& pf
        );


    //- Destructor
    virtual ~faPatchField() = default;


    // Member Functions

    // Access

        //- Return const-reference to the dimensioned internal field
        const DimensionedField<Type, areaMesh>& internalField() const noexcept
        {
            return internalField_;
        }

        //- Return const-reference to the internal field values
        const Field<Type>& primitiveField() const noexcept
        {
            return internalField_;
        }


        // Mapping

            //- Map (and resize as needed) from self given a mapping object
            virtual void autoMap
            (
                const faPatchFieldMapper&
            );

            //- Reverse map the given faPatchField onto this faPatchField
            virtual void rmap
            (
                const faPatchField<Type>&,
                const labelList&
            );


        // Evaluation

            //- Return patch-normal gradient
            virtual tmp<Field<Type>> snGrad() const;

            //- Return internal field next to patch
            virtual tmp<Field<Type>> patchInternalField() const;

            //- Extract internal field next to patch
            //  \param [out] pfld The extracted patch field.
            virtual void patchInternalField(Field<Type>& pfld) const;

            //- Return patchField on the opposite patch of a coupled patch
            virtual tmp<Field<Type>> patchNeighbourField() const
            {
                NotImplemented;
                return *this;
            }

            //- Update the coefficients associated with the patch field
            //  Sets Updated to true
            virtual void updateCoeffs();

            //- Initialise the evaluation of the patch field
            virtual void initEvaluate
            (
                const Pstream::commsTypes commsType =
                    Pstream::commsTypes::blocking
            )
            {}

            //- Evaluate the patch field, sets updated() to false
            virtual void evaluate
            (
                const Pstream::commsTypes commsType =
                    Pstream::commsTypes::blocking
            );

            //- Initialise the evaluation of the patch field after a local
            //  operation
            virtual void initEvaluateLocal
            (
                const Pstream::commsTypes commsType =
                    Pstream::commsTypes::blocking
            )
            {}

            //- Evaluate the patch field after a local operation (e.g. *=)
            virtual void evaluateLocal
            (
                const Pstream::commsTypes commsType =
                    Pstream::commsTypes::blocking
            )
            {}

            //- Return the matrix diagonal coefficients corresponding to the
            //- evaluation of the value of this patchField with given weights
            virtual tmp<Field<Type>> valueInternalCoeffs
            (
                const tmp<Field<scalar>>&
            ) const
            {
                NotImplemented;
                return *this;
            }

            //- Return the matrix source coefficients corresponding to the
            //- evaluation of the value of this patchField with given weights
            virtual tmp<Field<Type>> valueBoundaryCoeffs
            (
                const tmp<Field<scalar>>&
            ) const
            {
                NotImplemented;
                return *this;
            }

            //- Return the matrix diagonal coefficients corresponding to the
            //- evaluation of the gradient of this patchField
            virtual tmp<Field<Type>> gradientInternalCoeffs() const
            {
                NotImplemented;
                return *this;
            }

            //- Return the matrix source coefficients corresponding to the
            //- evaluation of the gradient of this patchField
            virtual tmp<Field<Type>> gradientBoundaryCoeffs() const
            {
                NotImplemented;
                return *this;
            }


    // Other

        //- Write
        virtual void write(Ostream& os) const;

        //- Check against given patch field
        void check(const faPatchField<Type>&) const;


    // Member Operators

        virtual void operator=(const UList<Type>&);

        virtual void operator=(const faPatchField<Type>&);
        virtual void operator+=(const faPatchField<Type>&);
        virtual void operator-=(const faPatchField<Type>&);
        virtual void operator*=(const faPatchField<scalar>&);
        virtual void operator/=(const faPatchField<scalar>&);

        virtual void operator+=(const Field<Type>&);
        virtual void operator-=(const Field<Type>&);

        virtual void operator*=(const Field<scalar>&);
        virtual void operator/=(const Field<scalar>&);

        virtual void operator=(const Type&);
        virtual void operator+=(const Type&);
        virtual void operator-=(const Type&);
        virtual void operator*=(const scalar);
        virtual void operator/=(const scalar);


        // Force an assignment irrespective of form of patch

        virtual void operator==(const faPatchField<Type>&);
        virtual void operator==(const Field<Type>&);
        virtual void operator==(const Type&);

        // Prevent automatic comparison rewriting (c++20)
        bool operator!=(const faPatchField<Type>&) const = delete;
        bool operator!=(const Field<Type>&) const = delete;
        bool operator!=(const Type&) const = delete;


    // Ostream Operator

        friend Ostream& operator<< <Type>(Ostream&, const faPatchField<Type>&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "fields/faPatchFields/faPatchField/faPatchField.C"
    #include "fields/faPatchFields/faPatchField/faPatchFieldNew.C"
    #include "fields/faPatchFields/basic/calculated/calculatedFaPatchField.H"
    #include "fields/faPatchFields/basic/zeroGradient/zeroGradientFaPatchField.H"
#endif

// Runtime selection macros
#include "fields/faPatchFields/faPatchField/faPatchFieldMacros.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
