/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
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

Class
    Foam::treeDataTriSurface

Description
    Encapsulates data for (indexedOc)tree searches on a triSurface.

SourceFiles
    treeDataTriSurface.C

\*---------------------------------------------------------------------------*/

#ifndef treeDataTriSurface_H
#define treeDataTriSurface_H

#include "indexedOctree/treeDataPrimitivePatch.H"
#include "triSurface/triSurface.H"
#include "meshes/primitiveShapes/point/point.H"
#include "algorithms/indexedOctree/indexedOctree.H"
#include "meshes/primitiveShapes/volumeType/volumeType.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    typedef treeDataPrimitivePatch<triSurface> treeDataTriSurface;

    //- Template specialisation of getVolumeType for treeDataTriSurface
    template<>
    volumeType treeDataPrimitivePatch<triSurface>::getVolumeType
    (
        const indexedOctree<treeDataPrimitivePatch<triSurface>>& oc,
        const point& sample
    ) const;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
