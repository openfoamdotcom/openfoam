/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2018 OpenCFD Ltd.
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
    Foam::simplifiedMeshes::hexCellFvMesh

Description
    Generates a single hex cell representation of a mesh

SourceFiles
    hexCellFvMesh.C

\*---------------------------------------------------------------------------*/

#ifndef simplifiedMeshes_hexCellFvMesh_H
#define simplifiedMeshes_hexCellFvMesh_H

#include "fvMesh/simplifiedFvMesh/simplifiedFvMesh/simplifiedFvMesh.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace simplifiedMeshes
{

/*---------------------------------------------------------------------------*\
                        Class hexCellFvMesh Declaration
\*---------------------------------------------------------------------------*/

class hexCellFvMesh
:
    public simplifiedFvMesh
{

public:

    //- Runtime type information
    TypeName("hexCellFvMesh");

    //- Constructor
    hexCellFvMesh(const Time& runTime, const scalar d = 1);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace simplifiedMeshes
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
