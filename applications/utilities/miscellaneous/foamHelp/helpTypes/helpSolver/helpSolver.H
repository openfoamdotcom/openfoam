/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2015 OpenFOAM Foundation
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
    Foam::helpSolver

Description
    This class provides help for solvers.  When no additional arguments
    are given, the utility outputs all known solvers.

    Usage:
    \plaintable
        \c -browse \<patch type\> | open documentation for object in browser
    \endplaintable

SeeAlso
    Foam::helpType

SourceFiles
    helpSolver.C

\*---------------------------------------------------------------------------*/

#ifndef helpSolver_H
#define helpSolver_H

#include "helpType/helpType.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace helpTypes
{

/*---------------------------------------------------------------------------*\
                         Class helpSolver Declaration
\*---------------------------------------------------------------------------*/

class helpSolver
:
    public helpType
{

public:

    //- Runtime type information
    TypeName("helpSolver");

    //- Constructor
    helpSolver();

    //- Destructor
    virtual ~helpSolver();


    // Member Functions

        //- Initialise - typically setting static variables,
        //  e.g. command line arguments
        virtual void init();

        //- Execute the help
        virtual void execute(const argList& args, const fvMesh& mesh);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace helpTypes
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
