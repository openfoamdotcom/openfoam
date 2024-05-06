/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016-2017 Wikki Ltd
    Copyright (C) 2021-2022 OpenCFD Ltd.
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
    makeFaMesh

Description
    Check a finiteArea mesh

Original Authors
    Zeljko Tukovic, FAMENA
    Hrvoje Jasak, Wikki Ltd.

\*---------------------------------------------------------------------------*/

#include "db/Time/TimeOpenFOAM.H"
#include "global/argList/argList.H"
#include "faMesh/faMesh.H"
#include "meshes/polyMesh/polyMesh.H"
#include "areaMesh/areaFaMesh.H"
#include "edgeMesh/edgeFaMesh.H"
#include "fields/areaFields/areaFields.H"
#include "fields/edgeFields/edgeFields.H"
#include "faMesh/faPatches/constraint/processor/processorFaPatch.H"
#include "output/vtk/patch/foamVtkIndPatchWriter.H"
#include "vtk/write/foamVtkLineWriter.H"
#include "faMesh/faMeshTools/faMeshTools.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addNote
    (
        "Check a finiteArea mesh"
    );

    argList::addBoolOption
    (
        "write-vtk",
        "Write mesh as a vtp (vtk) file for display or debugging"
    );

    argList::addOption
    (
        "geometryOrder",
        "N",
        "Test different geometry order - experimental!!",
        true  // Advanced option
    );

    #include "include/addRegionOption.H"
    #include "include/setRootCase.H"
    #include "include/createTime.H"
    #include "include/createNamedPolyMesh.H"

    int geometryOrder(1);
    if (args.readIfPresent("geometryOrder", geometryOrder))
    {
        Info<< "Setting faMesh::geometryOrder = " << geometryOrder << nl
            << "(experimental)" << nl << endl;

        faMesh::geometryOrder(geometryOrder);
    }

    // Create
    faMesh aMesh(mesh);

    Info<< "Time = " << runTime.timeName() << nl << endl;

    // Mesh information (verbose)
    faMeshTools::printMeshChecks(aMesh);

    if (args.found("write-vtk"))
    {
        #include "faMeshWriteVTK.H"
    }

    Info<< "\nEnd\n" << endl;

    return 0;
}


// ************************************************************************* //
