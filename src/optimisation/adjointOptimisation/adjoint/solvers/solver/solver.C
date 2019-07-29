/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2019 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
                            | Copyright (C) 2007-2019 PCOpt/NTUA
                            | Copyright (C) 2013-2019 FOSS GP
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

#include "solver.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(solver, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::solver::solver
(
    fvMesh& mesh,
    const word& managerType,
    const dictionary& dict
)
:
    localIOdictionary
    (
        IOobject
        (
            dict.dictName(),
            mesh.time().timeName(),
            fileName("uniform")/fileName("solvers"),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        word::null // avoid type checking since dictionary is read using the
                   // derived type name and type() will result in "solver" here
    ),
    mesh_(mesh),
    managerType_(managerType),
    dict_(dict),
    solverName_(dict.dictName()),
    active_(dict.lookupOrDefault<bool>("active", true)),
    optTypeSource_(nullptr)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::solver::~solver()
{
    optTypeSource_ = 0;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool Foam::solver::readDict(const dictionary& dict)
{
    dict_ = dict;

    // Note: Slightly dangerous to change active_ while the solver is
    // running. At the very least, this should trigger writing before stoping.
    // Additional problems if we have an adjontSolver corresponding to a
    // constraint. To be revisited
    //active_ = dict.lookupOrDefault<bool>("active", true);

    return true;
}


const Foam::word& Foam::solver::solverName() const
{
    return solverName_;
}


bool Foam::solver::active()
{
    return active_;
}


const Foam::dictionary& Foam::solver::dict() const
{
    return dict_;
}


void Foam::solver::restoreInitValues()
{
    // Does nothing in the base class
}


void Foam::solver::updateOptTypeSource
(
    const autoPtr<volScalarField>& optSourcePtr
)
{
    if (optSourcePtr.valid())
    {
        const volScalarField& optSource = optSourcePtr();
        optTypeSource_ = &optSource;
    }
}


// ************************************************************************* //