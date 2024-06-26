/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2015 OpenFOAM Foundation
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

Application
    zipUpMesh

Group
    grpMeshManipulationUtilities

Description
    Reads in a mesh with hanging vertices and 'zips' up the cells
    to guarantee that all polyhedral cells of valid shape are closed.

    Meshes with hanging vertices may occur as a result of split
    hex mesh conversion or integration or coupled math face pairs.

\*---------------------------------------------------------------------------*/

#include "global/argList/argList.H"
#include "db/Time/TimeOpenFOAM.H"
#include "meshes/polyMesh/polyMesh.H"
#include "polyMeshZipUpCells/polyMeshZipUpCells.H"
#include "primitives/bools/lists/boolList.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addNote
    (
        "Reads in a mesh with hanging vertices and 'zips' up the cells"
        " to guarantee that all polyhedral cells of valid shape are closed.\n"
        "Meshes with hanging vertices may occur as a result of split"
        " hex mesh conversion or integration or coupled math face pairs."
    );

    #include "include/addRegionOption.H"

    #include "include/setRootCase.H"
    #include "include/createTime.H"
    #include "include/createNamedPolyMesh.H"

    if (polyMeshZipUpCells(mesh))
    {
        Info<< "Writing zipped-up polyMesh to " << mesh.facesInstance() << endl;
        mesh.write();
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
