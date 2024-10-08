/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2020 OpenCFD Ltd.
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
    collapseEdges

Group
    grpMeshAdvancedUtilities

Description
    Collapses short edges and combines edges that are in line.

    - collapse short edges. Length of edges to collapse provided as argument.
    - merge two edges if they are in line. Maximum angle provided as argument.
    - remove unused points.
    - collapse faces:
        - with small areas to a single point
        - that have a high aspect ratio (i.e. sliver face) to a single edge

    Optionally checks the resulting mesh for bad faces and reduces the desired
    face length factor for those faces attached to the bad faces.

    When collapsing an edge with one point on the boundary it will leave
    the boundary point intact. When both points inside it chooses random. When
    both points on boundary random again.

Usage
    - collapseEdges [OPTION]

\*---------------------------------------------------------------------------*/

#include "global/argList/argList.H"
#include "db/Time/TimeOpenFOAM.H"
#include "db/Time/timeSelector.H"
#include "polyTopoChange/polyTopoChange.H"
#include "fvMesh/fvMesh.H"
#include "polyMeshFilter/polyMeshFilter.H"
#include "topoSet/topoSets/faceSet.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addNote
    (
        "Collapses small edges to a point.\n"
        "Optionally collapse small faces to a point and thin faces to an edge."
    );
    timeSelector::addOptions(true, false);  // constant(true), zero(false)
    argList::addBoolOption
    (
        "collapseFaces",
        "Collapse small and sliver faces as well as small edges"
    );

    argList::addOption
    (
        "collapseFaceSet",
        "faceSet",
        "Collapse faces that are in the supplied face set"
    );

    argList::addOption("dict", "file", "Alternative collapseDict");

    #include "include/addOverwriteOption.H"

    argList::noFunctionObjects();  // Never use function objects

    #include "include/setRootCase.H"
    #include "include/createTime.H"

    instantList timeDirs = timeSelector::selectIfPresent(runTime, args);

    #include "include/createNamedMesh.H"

    const word oldInstance = mesh.pointsInstance();

    const word dictName("collapseDict");
    #include "include/setSystemMeshDictionaryIO.H"

    Info<< "Reading " << dictIO.name() << nl << endl;

    IOdictionary collapseDict(dictIO);

    const bool overwrite = args.found("overwrite");

    const bool collapseFaces = args.found("collapseFaces");
    const bool collapseFaceSet = args.found("collapseFaceSet");

    if (collapseFaces && collapseFaceSet)
    {
        FatalErrorInFunction
            << "Both face zone collapsing and face collapsing have been"
            << "selected. Choose only one of:" << nl
            << "    -collapseFaces" << nl
            << "    -collapseFaceSet <faceSet>"
            << abort(FatalError);
    }


    // maintain indirectPatchFaces if it is there (default) or force
    // (if collapseFaceSet option provided)
    word faceSetName("indirectPatchFaces");
    IOobject::readOption readFlag = IOobject::READ_IF_PRESENT;

    if (args.readIfPresent("collapseFaceSet", faceSetName))
    {
        readFlag = IOobject::MUST_READ;
    }


    labelIOList pointPriority
    (
        IOobject
        (
            "pointPriority",
            runTime.timeName(),
            runTime,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        labelList(mesh.nPoints(), labelMin)
    );
    forAll(timeDirs, timeI)
    {
        runTime.setTime(timeDirs[timeI], timeI);

        Info<< "Time = " << runTime.timeName() << endl;

        autoPtr<polyMeshFilter> meshFilterPtr;

        label nBadFaces = 0;

        faceSet indirectPatchFaces
        (
            mesh,
            faceSetName,
            readFlag,
            IOobject::AUTO_WRITE
        );
        Info<< "Read faceSet " << indirectPatchFaces.name()
            << " with "
            << returnReduce(indirectPatchFaces.size(), sumOp<label>())
            << " faces" << endl;


        {
            meshFilterPtr.reset
            (
                new polyMeshFilter(mesh, pointPriority, collapseDict)
            );
            polyMeshFilter& meshFilter = meshFilterPtr();

            // newMesh will be empty until it is filtered
            const autoPtr<fvMesh>& newMesh = meshFilter.filteredMesh();

            // Filter small edges only. This reduces the number of faces so that
            // the face filtering is sped up.
            nBadFaces = meshFilter.filterEdges(0);
            {
                polyTopoChange meshMod(newMesh());

                meshMod.changeMesh(mesh, false);

                polyMeshFilter::copySets(newMesh(), mesh);
            }

            pointPriority = *(meshFilter.pointPriority());
        }

        if (collapseFaceSet)
        {
            meshFilterPtr.reset
            (
                new polyMeshFilter(mesh, pointPriority, collapseDict)
            );
            polyMeshFilter& meshFilter = meshFilterPtr();

            const autoPtr<fvMesh>& newMesh = meshFilter.filteredMesh();

            // Filter faces. Pass in the number of bad faces that are present
            // from the previous edge filtering to use as a stopping criterion.
            meshFilter.filter(indirectPatchFaces);
            {
                polyTopoChange meshMod(newMesh());

                meshMod.changeMesh(mesh, false);

                polyMeshFilter::copySets(newMesh(), mesh);
            }

            pointPriority = *(meshFilter.pointPriority());
        }

        if (collapseFaces)
        {
            meshFilterPtr.reset
            (
                new polyMeshFilter(mesh, pointPriority, collapseDict)
            );
            polyMeshFilter& meshFilter = meshFilterPtr();

            const autoPtr<fvMesh>& newMesh = meshFilter.filteredMesh();

            // Filter faces. Pass in the number of bad faces that are present
            // from the previous edge filtering to use as a stopping criterion.
            meshFilter.filter(nBadFaces);
            {
                polyTopoChange meshMod(newMesh());

                meshMod.changeMesh(mesh, false);

                polyMeshFilter::copySets(newMesh(), mesh);
            }

            pointPriority = *(meshFilter.pointPriority());
        }

        // Write resulting mesh
        if (!overwrite)
        {
            ++runTime;
        }
        else
        {
            mesh.setInstance(oldInstance);
        }

        Info<< nl << "Writing collapsed mesh to time "
            << runTime.timeName() << nl << endl;

        mesh.write();
        pointPriority.write();
    }

    Info<< nl;
    runTime.printExecutionTime(Info);

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
