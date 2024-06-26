/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2013-2016 OpenFOAM Foundation
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

Description
    Detect point pinches

\*---------------------------------------------------------------------------*/

#include "global/argList/argList.H"
#include "meshes/primitiveMesh/PatchTools/PatchTools.H"
#include "db/Time/TimeOpenFOAM.H"
#include "meshes/polyMesh/polyMesh.H"
#include "algorithms/PatchEdgeFaceWave/patchEdgeFaceRegions.H"
#include "algorithms/PatchEdgeFaceWave/PatchEdgeFaceWave.H"
#include "parallel/globalIndex/globalIndex.H"
#include "meshes/polyMesh/syncTools/syncTools.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


// Main program:

int main(int argc, char *argv[])
{
    argList::addArgument("patch");

    #include "include/setRootCase.H"
    #include "include/createTime.H"

    const word patchName = args[1];

    #include "include/createPolyMesh.H"

    Info<< "Mesh read in = "
        << runTime.cpuTimeIncrement()
        << " s\n" << endl << endl;


    const polyBoundaryMesh& pbm = mesh.boundaryMesh();
    label patchi = pbm.findPatchID(patchName);
    const polyPatch& patch = pbm[patchi];

    Info<< "Patch:" << patch.name() << endl;



    // Data on all edges and faces
    List<patchEdgeFaceRegions> allEdgeInfo(patch.nEdges());
    List<patchEdgeFaceRegions> allFaceInfo(patch.size());

    // Determine parallel global indexing
    const globalIndex globalNumbering(patch.size());

    DynamicList<label> changedEdges(4*patch.size());
    DynamicList<patchEdgeFaceRegions> changedInfo(changedEdges.size());

    forAll(patch, facei)
    {
        const labelList& fEdges = patch.faceEdges()[facei];

        label globalFacei = globalNumbering.toGlobal(facei);

        forAll(fEdges, i)
        {
            changedEdges.push_back(fEdges[i]);
            changedInfo.emplace_back(labelPair(globalFacei, globalFacei));
        }
    }

    // Walk
    PatchEdgeFaceWave
    <
        primitivePatch,
        patchEdgeFaceRegions
    > calc
    (
        mesh,
        patch,
        changedEdges,
        changedInfo,
        allEdgeInfo,
        allFaceInfo,
        returnReduce(patch.nEdges(), sumOp<label>())
    );


    Info<< "Time now = " << runTime.timeName() << endl;


    // Detect points with multiple regions
    labelList duplicateRegion(patch.nPoints(), -1);
    {
        labelList currentRegion(patch.nPoints(), -1);

        forAll(patch.localFaces(), facei)
        {
            const face& f = patch.localFaces()[facei];

            forAll(f, fp)
            {
                label faceRegion = allFaceInfo[facei].regions()[fp];

                label pointi = f[fp];

                if (currentRegion[pointi] == -1)
                {
                    currentRegion[pointi] = faceRegion;
                }
                else if (currentRegion[pointi] != faceRegion)
                {
                    if (duplicateRegion[pointi] == -1)
                    {
                        Pout<< "Multi region point:"
                            << patch.localPoints()[pointi]
                            << " with region:" << currentRegion[pointi]
                            << " and region:" << faceRegion
                            << endl;
                        duplicateRegion[pointi] = currentRegion[pointi];
                    }
                }
            }
        }
    }


    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
