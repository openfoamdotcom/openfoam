/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2013 OpenFOAM Foundation
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

#include "meshes/primitiveMesh/PatchTools/PatchTools.H"

#include "meshes/primitiveMesh/PatchTools/PatchToolsCheck.C"
#include "meshes/primitiveMesh/PatchTools/PatchToolsEdgeOwner.C"
#include "meshes/primitiveMesh/PatchTools/PatchToolsGatherAndMerge.C"
#include "meshes/primitiveMesh/PatchTools/PatchToolsSearch.C"
#include "meshes/primitiveMesh/PatchTools/PatchToolsSortEdges.C"
#include "meshes/primitiveMesh/PatchTools/PatchToolsSortPoints.C"
#include "meshes/primitiveMesh/PatchTools/PatchToolsNormals.C"
#include "meshes/primitiveMesh/PatchTools/PatchToolsMatch.C"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


// ************************************************************************* //
