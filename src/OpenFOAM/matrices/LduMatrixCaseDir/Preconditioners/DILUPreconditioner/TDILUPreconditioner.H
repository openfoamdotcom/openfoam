/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2019 OpenCFD Ltd.
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
    Foam::TDILUPreconditioner

Description
    Simplified diagonal-based incomplete LU preconditioner for asymmetric
    matrices.

    The inverse (reciprocal for scalar) of the preconditioned diagonal is
    calculated and stored.

SourceFiles
    TDILUPreconditioner.C

\*---------------------------------------------------------------------------*/

#ifndef TDILUPreconditioner_H
#define TDILUPreconditioner_H

#include "matrices/LduMatrixCaseDir/LduMatrix/LduMatrixPascal.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class TDILUPreconditioner Declaration
\*---------------------------------------------------------------------------*/

template<class Type, class DType, class LUType>
class TDILUPreconditioner
:
    public LduMatrix<Type, DType, LUType>::preconditioner
{
    // Private data

        //- The inverse (reciprocal for scalar) preconditioned diagonal
        Field<DType> rD_;


public:

    //- Runtime type information
    TypeName("DILU");


    // Constructors

        //- Construct from matrix components and preconditioner data dictionary
        TDILUPreconditioner
        (
            const typename LduMatrix<Type, DType, LUType>::solver& sol,
            const dictionary& preconditionerDict
        );


    // Destructor

        virtual ~TDILUPreconditioner() = default;


    // Member Functions

        //- Calculate the reciprocal of the preconditioned diagonal
        static void calcInvD
        (
            Field<DType>& rD,
            const LduMatrix<Type, DType, LUType>& matrix
        );

        //- Return wA the preconditioned form of residual rA
        virtual void precondition
        (
            Field<Type>& wA,
            const Field<Type>& rA
        ) const;

        //- Return wT the transpose-matrix preconditioned form of
        //  residual rT.
        virtual void preconditionT
        (
            Field<Type>& wT,
            const Field<Type>& rT
        ) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "matrices/LduMatrixCaseDir/Preconditioners/DILUPreconditioner/TDILUPreconditioner.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
