/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2019-2021 OpenCFD Ltd.
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

#include "meshes/polyMesh/zones/cellZone/cellZone.H"
#include "db/dictionary/dictionary.H"

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::autoPtr<Foam::cellZone> Foam::cellZone::New
(
    const word& name,
    const dictionary& dict,
    const label index,
    const cellZoneMesh& zm
)
{
    DebugInFunction << "Constructing cellZone " << name << endl;

    const word zoneType(dict.get<word>("type"));

    auto* ctorPtr = dictionaryConstructorTable(zoneType);

    if (!ctorPtr)
    {
        FatalIOErrorInLookup
        (
            dict,
            "cellZone",
            zoneType,
            *dictionaryConstructorTablePtr_
        ) << exit(FatalIOError);
    }

    return autoPtr<cellZone>(ctorPtr(name, dict, index, zm));
}


// ************************************************************************* //
