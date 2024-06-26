/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011 OpenFOAM Foundation
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
    Foam::diagonalPreconditioner

Group
    grpLduMatrixPreconditioners

Description
    Diagonal preconditioner for both symmetric and asymmetric matrices.

    The reciprocal of the diagonal is calculated and stored for reuse
    because on most systems '*' is faster than '/'.

SourceFiles
    diagonalPreconditioner.C

\*---------------------------------------------------------------------------*/

#ifndef diagonalPreconditioner_H
#define diagonalPreconditioner_H

#include "matrices/lduMatrix/lduMatrix/lduMatrix.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class diagonalPreconditioner Declaration
\*---------------------------------------------------------------------------*/

class diagonalPreconditioner
:
    public lduMatrix::preconditioner
{
    // Private data

        //- The reciprocal diagonal
        solveScalarField rD;


    // Private Member Functions

        //- No copy construct
        diagonalPreconditioner(const diagonalPreconditioner&) = delete;

        //- No copy assignment
        void operator=(const diagonalPreconditioner&) = delete;


public:

    //- Runtime type information
    TypeName("diagonal");


    // Constructors

        //- Construct from matrix components and preconditioner solver controls
        diagonalPreconditioner
        (
            const lduMatrix::solver&,
            const dictionary& solverControlsUnused
        );


    //- Destructor
    virtual ~diagonalPreconditioner() = default;


    // Member Functions

        //- Return wA the preconditioned form of residual rA
        virtual void precondition
        (
            solveScalarField& wA,
            const solveScalarField& rA,
            const direction cmpt=0
        ) const;

        //- Return wT the transpose-matrix preconditioned form of residual rT.
        virtual void preconditionT
        (
            solveScalarField& wT,
            const solveScalarField& rT,
            const direction cmpt=0
        ) const
        {
            return precondition(wT, rT, cmpt);
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
