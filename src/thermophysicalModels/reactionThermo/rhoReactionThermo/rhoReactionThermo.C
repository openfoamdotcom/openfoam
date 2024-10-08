/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2012 OpenFOAM Foundation
    Copyright (C) 2017 OpenCFD Ltd.
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

#include "rhoReactionThermo/rhoReactionThermo.H"
#include "fvMesh/fvMesh.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(rhoReactionThermo, 0);
    defineRunTimeSelectionTable(rhoReactionThermo, fvMesh);
    defineRunTimeSelectionTable(rhoReactionThermo, fvMeshDictPhase);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::rhoReactionThermo::rhoReactionThermo
(
    const fvMesh& mesh,
    const word& phaseName
)
:
    rhoThermo(mesh, phaseName)
{}


Foam::rhoReactionThermo::rhoReactionThermo
(
    const fvMesh& mesh,
    const word& phaseName,
    const word& dictName
)
:
    rhoThermo(mesh, phaseName, dictName)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

Foam::autoPtr<Foam::rhoReactionThermo> Foam::rhoReactionThermo::New
(
    const fvMesh& mesh,
    const word& phaseName
)
{
    return basicThermo::New<rhoReactionThermo>(mesh, phaseName);
}


Foam::autoPtr<Foam::rhoReactionThermo> Foam::rhoReactionThermo::New
(
    const fvMesh& mesh,
    const word& phaseName,
    const word& dictName
)
{
    return basicThermo::New<rhoReactionThermo>(mesh, phaseName, dictName);
}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::rhoReactionThermo::~rhoReactionThermo()
{}


// ************************************************************************* //
