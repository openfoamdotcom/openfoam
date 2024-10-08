/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2020 OpenFOAM Foundation
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

Description
    private member of meshToMesh0.
    Calculates mesh to mesh addressing pattern (for each cell from one mesh
    find the closest cell centre in the other mesh).

\*---------------------------------------------------------------------------*/

#include "meshToMesh0/meshToMesh0.H"

#include "algorithms/indexedOctree/treeDataCell.H"
#include "indexedOctree/treeDataFace.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::meshToMesh0::calcAddressing()
{
    DebugInFunction
        << "Calculating mesh-to-mesh cell addressing" << endl;

    // set reference to cells
    const cellList& fromCells = fromMesh_.cells();
    const pointField& fromPoints = fromMesh_.points();

    // In an attempt to preserve the efficiency of linear search and prevent
    // failure, a RESCUE mechanism will be set up. Here, we shall mark all
    // cells next to the solid boundaries. If such a cell is found as the
    // closest, the relationship between the origin and cell will be examined.
    // If the origin is outside the cell, a global n-squared search is
    // triggered.

    // SETTING UP RESCUE

    // visit all boundaries and mark the cell next to the boundary.

    DebugInFunction << "Setting up rescue" << endl;

    List<bool> boundaryCell(fromCells.size(), false);

    // set reference to boundary
    const polyPatchList& patchesFrom = fromMesh_.boundaryMesh();

    forAll(patchesFrom, patchi)
    {
        // get reference to cells next to the boundary
        const labelUList& bCells = patchesFrom[patchi].faceCells();

        forAll(bCells, facei)
        {
            boundaryCell[bCells[facei]] = true;
        }
    }

    treeBoundBox meshBb(fromPoints);
    treeBoundBox shiftedBb(meshBb);

    scalar typDim = meshBb.avgDim()/(2.0*cbrt(scalar(fromCells.size())));
    shiftedBb.max() += vector::uniform(typDim);

    DebugInfo
        << "\nMesh" << nl
        << "   bounding box           : " << meshBb << nl
        << "   bounding box (shifted) : " << shiftedBb << nl
        << "   typical dimension      : " << shiftedBb.avgDim() << endl;

    indexedOctree<treeDataCell> cellTree
    (
        treeDataCell(fromMesh_, polyMesh::CELL_TETS),
        shiftedBb,      // overall bounding box
        8,              // maxLevel
        10,             // leafsize
        6.0             // duplicity
    );

    if (debug)
    {
        cellTree.print(Pout, false, 0);
    }

    cellAddresses
    (
        cellAddressing_,
        toMesh_.cellCentres(),
        fromMesh_,
        boundaryCell,
        cellTree
    );

    forAll(toMesh_.boundaryMesh(), patchi)
    {
        const polyPatch& toPatch = toMesh_.boundaryMesh()[patchi];

        if (cuttingPatches_.found(toPatch.name()))
        {
            boundaryAddressing_[patchi].setSize(toPatch.size());

            cellAddresses
            (
                boundaryAddressing_[patchi],
                toPatch.faceCentres(),
                fromMesh_,
                boundaryCell,
                cellTree
            );
        }
        else if
        (
            patchMap_.found(toPatch.name())
         && fromMeshPatches_.found(patchMap_.find(toPatch.name())())
        )
        {
            const polyPatch& fromPatch = fromMesh_.boundaryMesh()
            [
                fromMeshPatches_.find(patchMap_.find(toPatch.name())())()
            ];

            if (fromPatch.empty())
            {
                WarningInFunction
                    << "Source patch " << fromPatch.name()
                    << " has no faces. Not performing mapping for it."
                    << endl;
                boundaryAddressing_[patchi].setSize(toPatch.size());
                boundaryAddressing_[patchi] = -1;
            }
            else
            {
                treeBoundBox wallBb(fromPatch.localPoints());
                treeBoundBox shiftedBb(wallBb);

                scalar typDim =
                    wallBb.avgDim()/(2.0*sqrt(scalar(fromPatch.size())));

                shiftedBb.max() += vector::uniform(typDim);

                // Note: allow more levels than in meshSearch. Assume patch
                // is not as big as all boundary faces
                indexedOctree<treeDataFace> faceTree
                (
                    treeDataFace(fromPatch),
                    shiftedBb,  // overall search domain
                    12,         // maxLevel
                    10,         // leafsize
                    6.0         // duplicity
                );

                const vectorField::subField centresToBoundary =
                    toPatch.faceCentres();

                boundaryAddressing_[patchi].setSize(toPatch.size());

                scalar distSqr = wallBb.magSqr();

                forAll(toPatch, toi)
                {
                    boundaryAddressing_[patchi][toi] = faceTree.findNearest
                    (
                        centresToBoundary[toi],
                        distSqr
                    ).index();
                }
            }
        }
    }

    DebugInFunction
        << "Finished calculating mesh-to-mesh cell addressing" << endl;
}


void Foam::meshToMesh0::cellAddresses
(
    labelList& cellAddressing_,
    const pointField& points,
    const fvMesh& fromMesh,
    const List<bool>& boundaryCell,
    const indexedOctree<treeDataCell>& cellTree
) const
{
    // the implemented search method is a simple neighbour array search.
    // It starts from a cell zero, searches its neighbours and finds one
    // which is nearer to the target point than the current position.
    // The location of the "current position" is reset to that cell and
    // search through the neighbours continues. The search is finished
    // when all the neighbours of the cell are farther from the target
    // point than the current cell

    // set curCell label to zero (start)
    label curCell = 0;

    // set reference to cell to cell addressing
    const vectorField& centresFrom = fromMesh.cellCentres();
    const labelListList& cc = fromMesh.cellCells();

    forAll(points, toI)
    {
        // pick up target position
        const vector& p = points[toI];

        // set the sqr-distance
        scalar distSqr = p.distSqr(centresFrom[curCell]);

        bool closer;

        do
        {
            closer = false;

            // set the current list of neighbouring cells
            const labelList& neighbours = cc[curCell];

            forAll(neighbours, nI)
            {
                scalar curDistSqr = p.distSqr(centresFrom[neighbours[nI]]);

                // search through all the neighbours.
                // If the cell is closer, reset current cell and distance
                if (curDistSqr < (1 - SMALL)*distSqr)
                {
                    curCell = neighbours[nI];
                    distSqr = curDistSqr;
                    closer = true;    // a closer neighbour has been found
                }
            }
        } while (closer);

        cellAddressing_[toI] = -1;

        // Check point is actually in the nearest cell
        if (fromMesh.pointInCell(p, curCell))
        {
            cellAddressing_[toI] = curCell;
        }
        else
        {
            // If curCell is a boundary cell then the point maybe either outside
            // the domain or in an other region of the doamin, either way use
            // the octree search to find it.
            if (boundaryCell[curCell])
            {
                cellAddressing_[toI] = cellTree.findInside(p);

                if (cellAddressing_[toI] != -1)
                {
                    curCell = cellAddressing_[toI];
                }
            }
            else
            {
                // If not on the boundary search the neighbours
                bool found = false;

                // set the current list of neighbouring cells
                const labelList& neighbours = cc[curCell];

                forAll(neighbours, nI)
                {
                    // search through all the neighbours.
                    // If point is in neighbour reset current cell
                    if (fromMesh.pointInCell(p, neighbours[nI]))
                    {
                        cellAddressing_[toI] = neighbours[nI];
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    // If still not found search the neighbour-neighbours

                    // set the current list of neighbouring cells
                    const labelList& neighbours = cc[curCell];

                    forAll(neighbours, nI)
                    {
                        // set the current list of neighbour-neighbouring cells
                        const labelList& nn = cc[neighbours[nI]];

                        forAll(nn, nI)
                        {
                            // search through all the neighbours.
                            // If point is in neighbour reset current cell
                            if (fromMesh.pointInCell(p, nn[nI]))
                            {
                                cellAddressing_[toI] = nn[nI];
                                found = true;
                                break;
                            }
                        }
                        if (found) break;
                    }
                }

                if (!found)
                {
                    // Still not found so use the octree
                    cellAddressing_[toI] = cellTree.findInside(p);

                    if (cellAddressing_[toI] != -1)
                    {
                        curCell = cellAddressing_[toI];
                    }
                }
            }
        }
    }
}


// ************************************************************************* //
