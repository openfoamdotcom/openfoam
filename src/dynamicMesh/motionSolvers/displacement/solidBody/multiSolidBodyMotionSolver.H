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
    Foam::multiSolidBodyMotionSolver

Description
    Solid-body motion of the mesh specified by a run-time selectable
    motion function.

SourceFiles
    multiSolidBodyMotionSolver.C

\*---------------------------------------------------------------------------*/

#ifndef Foam_multiSolidBodyMotionSolver_H
#define Foam_multiSolidBodyMotionSolver_H

#include "motionSolvers/displacement/points0/points0MotionSolver.H"
#include "motionSolvers/displacement/solidBody/solidBodyMotionFunctions/solidBodyMotionFunction/solidBodyMotionFunction.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                   Class multiSolidBodyMotionSolver Declaration
\*---------------------------------------------------------------------------*/

class multiSolidBodyMotionSolver
:
    public points0MotionSolver
{
    // Private Data

        //- The motion control function
        PtrList<solidBodyMotionFunction> SBMFs_;

        //- Points to move per cellZone
        labelListList pointIDs_;


    // Private Member Functions

        //- No copy construct
        multiSolidBodyMotionSolver(const multiSolidBodyMotionSolver&) = delete;

        //- No copy assignment
        void operator=(const multiSolidBodyMotionSolver&) = delete;


public:

    //- Runtime type information
    TypeName("multiSolidBodyMotionSolver");


    // Constructors

        //- Construct from mesh and dictionary
        multiSolidBodyMotionSolver
        (
            const polyMesh& mesh,
            const IOdictionary& dict
        );


    //- Destructor
    virtual ~multiSolidBodyMotionSolver() = default;


    // Member Functions

        //- Return point location obtained from the current motion field
        virtual tmp<pointField> curPoints() const;

        //- Solve for motion
        virtual void solve()
        {}
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
