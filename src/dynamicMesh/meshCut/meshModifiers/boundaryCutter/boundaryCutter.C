/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2019 OpenCFD Ltd.
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

#include "meshCut/meshModifiers/boundaryCutter/boundaryCutter.H"
#include "meshes/polyMesh/polyMesh.H"
#include "polyTopoChange/polyTopoChange.H"
#include "polyTopoChange/addObject/polyAddCell.H"
#include "polyTopoChange/addObject/polyAddFace.H"
#include "polyTopoChange/addObject/polyAddPoint.H"
#include "polyTopoChange/modifyObject/polyModifyFace.H"
#include "polyTopoChange/modifyObject/polyModifyPoint.H"
#include "meshes/polyMesh/mapPolyMesh/mapPolyMesh.H"
#include "meshTools/meshTools.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(boundaryCutter, 0);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::boundaryCutter::getFaceInfo
(
    const label facei,
    label& patchID,
    label& zoneID,
    label& zoneFlip
) const
{
    patchID = -1;

    if (!mesh_.isInternalFace(facei))
    {
        patchID = mesh_.boundaryMesh().whichPatch(facei);
    }

    zoneID = mesh_.faceZones().whichZone(facei);

    zoneFlip = false;

    if (zoneID >= 0)
    {
        const faceZone& fZone = mesh_.faceZones()[zoneID];

        zoneFlip = fZone.flipMap()[fZone.whichFace(facei)];
    }
}


// Adds additional vertices (from edge cutting) to face. Used for faces which
// are not split but still might use edge that has been cut.
Foam::face Foam::boundaryCutter::addEdgeCutsToFace
(
    const label facei,
    const Map<labelList>& edgeToAddedPoints
) const
{
    const edgeList& edges = mesh_.edges();
    const face& f = mesh_.faces()[facei];
    const labelList& fEdges = mesh_.faceEdges()[facei];

    // Storage for face
    DynamicList<label> newFace(2 * f.size());

    forAll(f, fp)
    {
        // Duplicate face vertex .
        newFace.append(f[fp]);

        // Check if edge has been cut.
        label v1 = f.nextLabel(fp);

        label edgeI = meshTools::findEdge(edges, fEdges, f[fp], v1);

        const auto fnd = edgeToAddedPoints.cfind(edgeI);

        if (fnd.good())
        {
            // edge has been cut. Introduce new vertices. Check order.
            const labelList& addedPoints = fnd();

            if (edges[edgeI].start() == f[fp])
            {
                // Introduce in same order.
                forAll(addedPoints, i)
                {
                    newFace.append(addedPoints[i]);
                }
            }
            else
            {
                // Introduce in opposite order.
                forAllReverse(addedPoints, i)
                {
                    newFace.append(addedPoints[i]);
                }
            }
        }
    }

    face returnFace;
    returnFace.transfer(newFace);

    if (debug)
    {
        Pout<< "addEdgeCutsToFace:" << nl
            << "    from : " << f << nl
            << "    to   : " << returnFace << endl;
    }

    return returnFace;
}


void Foam::boundaryCutter::addFace
(
    const label facei,
    const face& newFace,

    bool& modifiedFace,     // have we already 'used' facei
    polyTopoChange& meshMod
) const
{
    // Information about old face
    label patchID, zoneID, zoneFlip;
    getFaceInfo(facei, patchID, zoneID, zoneFlip);
    label own = mesh_.faceOwner()[facei];
    label masterPoint = mesh_.faces()[facei][0];

    if (!modifiedFace)
    {
        meshMod.setAction
        (
            polyModifyFace
            (
                newFace,       // face
                facei,
                own,           // owner
                -1,            // neighbour
                false,         // flux flip
                patchID,       // patch for face
                false,         // remove from zone
                zoneID,        // zone for face
                zoneFlip       // face zone flip
            )
        );

        modifiedFace = true;
    }
    else
    {
        meshMod.setAction
        (
            polyAddFace
            (
                newFace,       // face
                own,           // owner
                -1,            // neighbour
                masterPoint,   // master point
                -1,            // master edge
                -1,            // master face for addition
                false,         // flux flip
                patchID,       // patch for face
                zoneID,        // zone for face
                zoneFlip       // face zone flip
            )
        );
    }
}



// Splits a face using the cut edges and modified points
bool Foam::boundaryCutter::splitFace
(
    const label facei,
    const Map<point>& pointToPos,
    const Map<labelList>& edgeToAddedPoints,
    polyTopoChange& meshMod
) const
{
    const edgeList& edges = mesh_.edges();
    const face& f = mesh_.faces()[facei];
    const labelList& fEdges = mesh_.faceEdges()[facei];

    // Count number of split edges and total number of splits.
    label nSplitEdges = 0;
    label nModPoints = 0;
    label nTotalSplits = 0;

    forAll(f, fp)
    {
        if (pointToPos.found(f[fp]))
        {
            nModPoints++;
            nTotalSplits++;
        }

        // Check if edge has been cut.
        label nextV = f.nextLabel(fp);

        label edgeI = meshTools::findEdge(edges, fEdges, f[fp], nextV);

        const auto fnd = edgeToAddedPoints.cfind(edgeI);

        if (fnd.good())
        {
            nSplitEdges++;
            nTotalSplits += fnd().size();
        }
    }

    if (debug)
    {
        Pout<< "Face:" << facei
            << " nModPoints:" << nModPoints
            << " nSplitEdges:" << nSplitEdges
            << " nTotalSplits:" << nTotalSplits << endl;
    }

    if (nSplitEdges == 0 && nModPoints == 0)
    {
        FatalErrorInFunction
            << " nSplitEdges:" << nSplitEdges
            << " nTotalSplits:" << nTotalSplits
            << abort(FatalError);
        return false;
    }
    else if (nSplitEdges + nModPoints == 1)
    {
        // single or multiple cuts on a single edge or single modified point
        // Don't cut and let caller handle this.
        Warning << "Face " << facei << " has only one edge cut " << endl;
        return false;
    }
    else
    {
        // So guaranteed to have two edges cut or points modified. Split face:
        // - find starting cut
        // - walk to next cut. Make face
        // - loop until face done.

        // Information about old face
        label patchID, zoneID, zoneFlip;
        getFaceInfo(facei, patchID, zoneID, zoneFlip);

        // Get face with new points on cut edges for ease of looping
        face extendedFace(addEdgeCutsToFace(facei, edgeToAddedPoints));

        // Find first added point. This is the starting vertex for splitting.
        label startFp = -1;

        forAll(extendedFace, fp)
        {
            if (extendedFace[fp] >= mesh_.nPoints())
            {
                startFp = fp;
                break;
            }
        }

        if (startFp == -1)
        {
            // No added point. Maybe there is a modified point?
            forAll(extendedFace, fp)
            {
                if (pointToPos.found(extendedFace[fp]))
                {
                    startFp = fp;
                    break;
                }
            }
        }

        if (startFp == -1)
        {
            FatalErrorInFunction
                << "Problem" << abort(FatalError);
        }

        // Have we already modified existing face (first face gets done
        // as modification; all following ones as polyAddFace)
        bool modifiedFace = false;

        // Example face:
        //    +--+
        //   /   |
        //  /    |
        // +     +
        //  \    |
        //   \   |
        //    +--+
        //
        // Needs to get split into:
        // - three 'side' faces a,b,c
        // - one middle face d
        //    +--+
        //   /|\A|
        //  / | \|
        // + C|D +
        //  \ | /|
        //   \|/B|
        //    +--+


        // Storage for new face
        DynamicList<label> newFace(extendedFace.size());

        label fp = startFp;

        forAll(extendedFace, i)
        {
            label pointi = extendedFace[fp];

            newFace.append(pointi);

            if
            (
                newFace.size() > 2
             && (
                    pointi >= mesh_.nPoints()
                 || pointToPos.found(pointi)
                )
            )
            {
                // Enough vertices to create a face from.
                face tmpFace;
                tmpFace.transfer(newFace);

                // Add face tmpFace
                addFace(facei, tmpFace, modifiedFace, meshMod);

                // Starting point is also the starting point for the new face
                newFace.append(extendedFace[startFp]);
                newFace.append(extendedFace[fp]);
            }

            fp = (fp+1) % extendedFace.size();
        }

        // Check final face.
        if (newFace.size() > 2)
        {
            // Enough vertices to create a face from.
            face tmpFace;
            tmpFace.transfer(newFace);

            // Add face tmpFace
            addFace(facei, tmpFace, modifiedFace, meshMod);
        }

        // Split something
        return true;
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::boundaryCutter::boundaryCutter(const polyMesh& mesh)
:
    mesh_(mesh),
    edgeAddedPoints_(),
    faceAddedPoint_()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::boundaryCutter::setRefinement
(
    const Map<point>& pointToPos,
    const Map<List<point>>& edgeToCuts,
    const Map<labelPair>& faceToSplit,
    const Map<point>& faceToFeaturePoint,
    polyTopoChange& meshMod
)
{
    // Clear and size maps here since mesh size will change.
    edgeAddedPoints_.clear();

    faceAddedPoint_.clear();
    faceAddedPoint_.reserve(faceToFeaturePoint.size());


    //
    // Points that just need to be moved
    // Note: could just as well be handled outside of setRefinement.
    //

    forAllConstIters(pointToPos, iter)
    {
        meshMod.setAction
        (
            polyModifyPoint
            (
                iter.key(), // point
                iter.val(), // position
                false,      // no zone
                -1,         // zone for point
                true        // supports a cell
            )
        );
    }


    //
    // Add new points along cut edges.
    //

    // Map from edge label to sorted list of points
    Map<labelList> edgeToAddedPoints(edgeToCuts.size());

    forAllConstIters(edgeToCuts, iter)
    {
        const label edgeI = iter.key();
        const List<point>& cuts = iter.val();

        const edge& e = mesh_.edges()[edgeI];

        // Sorted (from start to end) list of cuts on edge

        forAll(cuts, cutI)
        {
            // point on feature to move to
            const point& featurePoint = cuts[cutI];

            label addedPointi =
                meshMod.setAction
                (
                    polyAddPoint
                    (
                        featurePoint,               // point
                        e.start(),                  // master point
                        -1,                         // zone for point
                        true                        // supports a cell
                    )
                );

            auto fnd = edgeToAddedPoints.find(edgeI);

            if (fnd.good())
            {
                labelList& addedPoints = fnd();

                label sz = addedPoints.size();
                addedPoints.setSize(sz+1);
                addedPoints[sz] = addedPointi;
            }
            else
            {
                edgeToAddedPoints.insert(edgeI, labelList(1, addedPointi));
            }

            if (debug)
            {
                Pout<< "Added point " << addedPointi << " for edge " << edgeI
                    << " with cuts:" << edgeToAddedPoints[edgeI] << endl;
            }
        }
    }


    //
    // Introduce feature points.
    //

    forAllConstIters(faceToFeaturePoint, iter)
    {
        const label facei = iter.key();

        const face& f = mesh_.faces()[facei];

        if (faceToSplit.found(facei))
        {
            FatalErrorInFunction
                << "Face " << facei << " vertices " << f
                << " is both marked for face-centre decomposition and"
                << " diagonal splitting."
                << abort(FatalError);
        }

        if (mesh_.isInternalFace(facei))
        {
            FatalErrorInFunction
                << "Face " << facei << " vertices " << f
                << " is not an external face. Cannot split it"
                << abort(FatalError);
        }

        label addedPointi =
            meshMod.setAction
            (
                polyAddPoint
                (
                    iter.val(), // point
                    f[0],   // master point
                    -1,     // zone for point
                    true    // supports a cell
                )
            );

        faceAddedPoint_.insert(facei, addedPointi);

        if (debug)
        {
            Pout<< "Added point " << addedPointi << " for feature point "
                << iter.val() << " on face " << facei << " with centre "
                << mesh_.faceCentres()[facei] << endl;
        }
    }


    //
    // Split or retriangulate faces
    //


    // Maintain whether face has been updated (for -split edges
    // -new owner/neighbour)
    boolList faceUptodate(mesh_.nFaces(), false);


    // Triangulate faces containing feature points
    forAllConstIters(faceAddedPoint_, iter)
    {
        const label facei = iter.key();
        const label addedPointi = iter.val();

        // Get face with new points on cut edges.
        face newFace(addEdgeCutsToFace(facei, edgeToAddedPoints));

        // Information about old face
        label patchID, zoneID, zoneFlip;
        getFaceInfo(facei, patchID, zoneID, zoneFlip);
        label own = mesh_.faceOwner()[facei];
        label masterPoint = mesh_.faces()[facei][0];

        // Triangulate face around mid point

        face tri(3);

        forAll(newFace, fp)
        {
            label nextV = newFace.nextLabel(fp);

            tri[0] = newFace[fp];
            tri[1] = nextV;
            tri[2] = addedPointi;

            if (fp == 0)
            {
                // Modify the existing face.
                meshMod.setAction
                (
                    polyModifyFace
                    (
                        tri,                        // face
                        facei,
                        own,                        // owner
                        -1,                         // neighbour
                        false,                      // flux flip
                        patchID,                    // patch for face
                        false,                      // remove from zone
                        zoneID,                     // zone for face
                        zoneFlip                    // face zone flip
                    )
                );
            }
            else
            {
                // Add additional faces
                meshMod.setAction
                (
                    polyAddFace
                    (
                        tri,                        // face
                        own,                        // owner
                        -1,                         // neighbour
                        masterPoint,                // master point
                        -1,                         // master edge
                        -1,                         // master face for addition
                        false,                      // flux flip
                        patchID,                    // patch for face
                        zoneID,                     // zone for face
                        zoneFlip                    // face zone flip
                    )
                );
            }
        }

        faceUptodate[facei] = true;
    }


    // Diagonally split faces
    forAllConstIters(faceToSplit, iter)
    {
        const label facei = iter.key();

        const face& f = mesh_.faces()[facei];

        if (faceAddedPoint_.found(facei))
        {
            FatalErrorInFunction
                << "Face " << facei << " vertices " << f
                << " is both marked for face-centre decomposition and"
                << " diagonal splitting."
                << abort(FatalError);
        }


        // Get face with new points on cut edges.
        face newFace(addEdgeCutsToFace(facei, edgeToAddedPoints));

        // Information about old face
        label patchID, zoneID, zoneFlip;
        getFaceInfo(facei, patchID, zoneID, zoneFlip);
        label own = mesh_.faceOwner()[facei];
        label masterPoint = mesh_.faces()[facei][0];

        // Split face from one side of diagonal to other.
        const labelPair& diag = iter.val();

        label fp0 = newFace.find(f[diag[0]]);
        label fp1 = newFace.find(f[diag[1]]);

        if (fp0 == -1 || fp1 == -1 || fp0 == fp1)
        {
            FatalErrorInFunction
                << "Problem : Face " << facei << " vertices " << f
                << " newFace:" << newFace << " diagonal:" << f[diag[0]]
                << ' ' << f[diag[1]]
                << abort(FatalError);
        }

        // Replace existing face by newFace from fp0 to fp1 and add new one
        // from fp1 to fp0.

        DynamicList<label> newVerts(newFace.size());

        // Get vertices from fp0 to (and including) fp1
        label fp = fp0;

        do
        {
            newVerts.append(newFace[fp]);

            fp = (fp == newFace.size()-1 ? 0 : fp+1);

        } while (fp != fp1);

        newVerts.append(newFace[fp1]);


        // Modify the existing face.
        meshMod.setAction
        (
            polyModifyFace
            (
                face(newVerts.shrink()),    // face
                facei,
                own,                        // owner
                -1,                         // neighbour
                false,                      // flux flip
                patchID,                    // patch for face
                false,                      // remove from zone
                zoneID,                     // zone for face
                zoneFlip                    // face zone flip
            )
        );


        newVerts.clear();

        // Get vertices from fp1 to (and including) fp0

        do
        {
            newVerts.append(newFace[fp]);

            fp = (fp == newFace.size()-1 ? 0 : fp+1);

        } while (fp != fp0);

        newVerts.append(newFace[fp0]);

        // Add additional face
        meshMod.setAction
        (
            polyAddFace
            (
                face(newVerts.shrink()),    // face
                own,                        // owner
                -1,                         // neighbour
                masterPoint,                // master point
                -1,                         // master edge
                -1,                         // master face for addition
                false,                      // flux flip
                patchID,                    // patch for face
                zoneID,                     // zone for face
                zoneFlip                    // face zone flip
            )
        );

        faceUptodate[facei] = true;
    }


    // Split external faces without feature point but using cut edges.
    // Does right handed walk but not really.
    forAllConstIters(edgeToAddedPoints, iter)
    {
        const label edgeI = iter.key();

        const labelList& eFaces = mesh_.edgeFaces()[edgeI];

        forAll(eFaces, i)
        {
            label facei = eFaces[i];

            if (!faceUptodate[facei] && !mesh_.isInternalFace(facei))
            {
                // Is external face so split
                if (splitFace(facei, pointToPos, edgeToAddedPoints, meshMod))
                {
                    // Successful split
                    faceUptodate[facei] = true;
                }
            }
        }
    }


    // Add cut edges (but don't split) any other faces using any cut edge.
    // These can be external faces where splitFace hasn't cut them or
    // internal faces.
    forAllConstIters(edgeToAddedPoints, iter)
    {
        const label edgeI = iter.key();

        const labelList& eFaces = mesh_.edgeFaces()[edgeI];

        forAll(eFaces, i)
        {
            label facei = eFaces[i];

            if (!faceUptodate[facei])
            {
                // Renumber face to include split edges.
                face newFace(addEdgeCutsToFace(facei, edgeToAddedPoints));

                const label own = mesh_.faceOwner()[facei];

                label nei = -1;

                if (mesh_.isInternalFace(facei))
                {
                    nei = mesh_.faceNeighbour()[facei];
                }

                label patchID, zoneID, zoneFlip;
                getFaceInfo(facei, patchID, zoneID, zoneFlip);

                meshMod.setAction
                (
                    polyModifyFace
                    (
                        newFace,            // modified face
                        facei,              // label of face being modified
                        own,                // owner
                        nei,                // neighbour
                        false,              // face flip
                        patchID,            // patch for face
                        false,              // remove from zone
                        zoneID,             // zone for face
                        zoneFlip            // face flip in zone
                    )
                );

                faceUptodate[facei] = true;
            }
        }
    }

    // Convert edge to points storage from edge labels (not preserved)
    // to point labels
    edgeAddedPoints_.reserve(edgeToAddedPoints.size());

    forAllConstIters(edgeToAddedPoints, iter)
    {
        edgeAddedPoints_.insert(mesh_.edges()[iter.key()], iter.val());
    }
}


void Foam::boundaryCutter::updateMesh(const mapPolyMesh& morphMap)
{
    // Update stored labels for mesh change.

    //
    // Do faceToAddedPoint
    //

    {
        // Create copy since we're deleting entries.
        Map<label> newAddedPoints(faceAddedPoint_.capacity());

        forAllConstIters(faceAddedPoint_, iter)
        {
            const label oldFacei = iter.key();
            const label oldPointi = iter.val();

            const label newFacei = morphMap.reverseFaceMap()[oldFacei];
            const label newPointi = morphMap.reversePointMap()[oldPointi];

            if (newFacei >= 0 && newPointi >= 0)
            {
                newAddedPoints.insert(newFacei, newPointi);
            }
        }

        // Copy
        faceAddedPoint_.transfer(newAddedPoints);
    }


    //
    // Do edgeToAddedPoints
    //


    {
        // Create copy since we're deleting entries
        EdgeMap<labelList> newEdgeAddedPoints(edgeAddedPoints_.capacity());

        forAllConstIters(edgeAddedPoints_, iter)
        {
            const edge& e = iter.key();
            const labelList& addedPoints = iter.val();

            const label newStart = morphMap.reversePointMap()[e.start()];
            const label newEnd = morphMap.reversePointMap()[e.end()];

            if (newStart >= 0 && newEnd >= 0)
            {
                labelList newAddedPoints(addedPoints.size());
                label newI = 0;

                forAll(addedPoints, i)
                {
                    label newAddedPointi =
                        morphMap.reversePointMap()[addedPoints[i]];

                    if (newAddedPointi >= 0)
                    {
                        newAddedPoints[newI++] = newAddedPointi;
                    }
                }
                if (newI > 0)
                {
                    newAddedPoints.setSize(newI);

                    edge newE = edge(newStart, newEnd);

                    newEdgeAddedPoints.insert(newE, newAddedPoints);
                }
            }
        }

        // Copy
        edgeAddedPoints_.transfer(newEdgeAddedPoints);
    }
}


// ************************************************************************* //
