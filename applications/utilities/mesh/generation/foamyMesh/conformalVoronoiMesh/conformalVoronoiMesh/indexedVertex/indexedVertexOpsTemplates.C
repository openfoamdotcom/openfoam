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

\*---------------------------------------------------------------------------*/

#include "conformalVoronoiMesh/indexedVertex/indexedVertexOps.H"

// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

template<class VertexType>
Foam::scalar CGAL::indexedVertexOps::averageCellSize
(
    const VertexType& vA,
    const VertexType& vB
)
{
    // Arithmetic mean
    // return 0.5*(vA->targetCellSize() + vB->targetCellSize());

    // Geometric mean
    return sqrt(vA->targetCellSize()*vB->targetCellSize());

    // Harmonic mean
    // return
    //     2.0*(vA->targetCellSize()*vB->targetCellSize())
    //    /(vA->targetCellSize() + vB->targetCellSize());
}


template<class VertexType>
inline bool CGAL::indexedVertexOps::uninitialised(const VertexType& v)
{
    return v->type() == Foam::indexedVertexEnum::vtUnassigned;
}


// ************************************************************************* //
