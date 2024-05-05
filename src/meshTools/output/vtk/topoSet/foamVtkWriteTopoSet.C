/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2018-2021 OpenCFD Ltd.
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

#include "output/vtk/topoSet/foamVtkWriteTopoSet.H"
#include "meshes/polyMesh/polyMesh.H"
#include "topoSet/topoSets/topoSet.H"
#include "topoSet/topoSets/faceSet.H"
#include "topoSet/topoSets/cellSet.H"
#include "topoSet/topoSets/pointSet.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

bool Foam::vtk::writeTopoSet
(
    const polyMesh& mesh,
    const topoSet& set,
    const vtk::outputOptions opts,
    const fileName& file,
    bool parallel
)
{
    {
        const auto* ptr = isA<pointSet>(set);
        if (ptr)
        {
            return vtk::writePointSet(mesh, *ptr, opts, file, parallel);
        }
    }
    {
        const auto* ptr = isA<faceSet>(set);
        if (ptr)
        {
            return vtk::writeFaceSet(mesh, *ptr, opts, file, parallel);
        }
    }
    {
        const auto* ptr = isA<cellSet>(set);
        if (ptr)
        {
            return vtk::writeCellSetFaces(mesh, *ptr, opts, file, parallel);
        }
    }

    WarningInFunction
        << "No VTK writer for '" << set.type() << "' topoSet" << nl << endl;

    return false;
}


// ************************************************************************* //
