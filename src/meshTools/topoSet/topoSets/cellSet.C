/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011 OpenFOAM Foundation
    Copyright (C) 2016-2022 OpenCFD Ltd.
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

#include "topoSet/topoSets/cellSet.H"
#include "meshes/polyMesh/mapPolyMesh/mapPolyMesh.H"
#include "meshes/polyMesh/polyMesh.H"
#include "db/Time/TimeOpenFOAM.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"
#include "meshes/polyMesh/mapPolyMesh/mapDistribute/mapDistributePolyMesh.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
defineTypeNameAndDebug(cellSet, 0);

addToRunTimeSelectionTable(topoSet, cellSet, word);
addToRunTimeSelectionTable(topoSet, cellSet, size);
addToRunTimeSelectionTable(topoSet, cellSet, set);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::cellSet::cellSet(const IOobject& io)
:
    topoSet(io, typeName)
{}


Foam::cellSet::cellSet
(
    const polyMesh& mesh,
    const word& name,
    IOobjectOption::readOption rOpt,
    IOobjectOption::writeOption wOpt
)
:
    topoSet(mesh, typeName, name, rOpt, wOpt)
{
    // Make sure set within valid range
    check(mesh.nCells());
}


Foam::cellSet::cellSet
(
    const polyMesh& mesh,
    const word& name,
    const label size,
    IOobjectOption::writeOption wOpt
)
:
    topoSet(mesh, name, size, wOpt)
{}


Foam::cellSet::cellSet
(
    const polyMesh& mesh,
    const word& name,
    const topoSet& set,
    IOobjectOption::writeOption wOpt
)
:
    topoSet(mesh, name, set, wOpt)
{}


Foam::cellSet::cellSet
(
    const polyMesh& mesh,
    const word& name,
    const labelHashSet& labels,
    IOobjectOption::writeOption wOpt
)
:
    topoSet(mesh, name, labels, wOpt)
{}


Foam::cellSet::cellSet
(
    const polyMesh& mesh,
    const word& name,
    labelHashSet&& labels,
    IOobjectOption::writeOption wOpt
)
:
    topoSet(mesh, name, std::move(labels), wOpt)
{}


Foam::cellSet::cellSet
(
    const polyMesh& mesh,
    const word& name,
    const labelUList& labels,
    IOobjectOption::writeOption wOpt
)
:
    topoSet(mesh, name, labels, wOpt)
{}


// Database constructors (for when no mesh available)
Foam::cellSet::cellSet
(
    const Time& runTime,
    const word& name,
    IOobjectOption::readOption rOpt,
    IOobjectOption::writeOption wOpt
)
:
    topoSet
    (
        findIOobject(runTime, name, rOpt, wOpt),
        typeName
    )
{}


Foam::cellSet::cellSet
(
    const Time& runTime,
    const word& name,
    const label size,
    IOobjectOption::writeOption wOpt
)
:
    topoSet
    (
        findIOobject(runTime, name, IOobject::NO_READ, wOpt),
        size
    )
{}


Foam::cellSet::cellSet
(
    const Time& runTime,
    const word& name,
    const labelHashSet& labels,
    IOobjectOption::writeOption wOpt
)
:
    topoSet
    (
        findIOobject(runTime, name, IOobject::NO_READ, wOpt),
        labels
    )
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::label Foam::cellSet::maxSize(const polyMesh& mesh) const
{
    return mesh.nCells();
}


void Foam::cellSet::updateMesh(const mapPolyMesh& morphMap)
{
    updateLabels(morphMap.reverseCellMap());
}


void Foam::cellSet::distribute(const mapDistributePolyMesh& map)
{
    labelHashSet& labels = *this;

    boolList contents(map.nOldCells(), false);

    for (const label celli : labels)
    {
        contents.set(celli);
    }

    map.distributeCellData(contents);

    // The new length
    const label len = contents.size();

    // Count
    label n = 0;
    for (label i=0; i < len; ++i)
    {
        if (contents.test(i))
        {
            ++n;
        }
    }

    // Update labelHashSet

    labels.clear();
    labels.reserve(n);

    for (label i=0; i < len; ++i)
    {
        if (contents.test(i))
        {
            labels.set(i);
        }
    }
}


void Foam::cellSet::writeDebug
(
    Ostream& os,
    const primitiveMesh& mesh,
    const label maxLen
) const
{
    topoSet::writeDebug(os, mesh.cellCentres(), maxLen);
}


// ************************************************************************* //
