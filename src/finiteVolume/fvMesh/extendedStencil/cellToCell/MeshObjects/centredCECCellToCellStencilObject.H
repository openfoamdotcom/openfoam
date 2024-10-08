/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2013 OpenFOAM Foundation
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

Class
    Foam::centredCECCellToCellStencilObject

Description

SourceFiles

\*---------------------------------------------------------------------------*/

#ifndef centredCECCellToCellStencilObject_H
#define centredCECCellToCellStencilObject_H

#include "fvMesh/extendedStencil/cellToCell/extendedCentredCellToCellStencil.H"
#include "fvMesh/extendedStencil/cellToCell/globalIndexStencils/CECCellToCellStencil.H"
#include "meshes/MeshObject/MeshObject.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
              Class centredCECCellToCellStencilObject Declaration
\*---------------------------------------------------------------------------*/

class centredCECCellToCellStencilObject
:
    public MeshObject
    <
        fvMesh,
        TopologicalMeshObject,
        centredCECCellToCellStencilObject
    >,
    public extendedCentredCellToCellStencil
{

public:

    TypeName("centredCECCellToCellStencil");

    // Constructors

        //- Construct from uncompacted cell stencil
        explicit centredCECCellToCellStencilObject
        (
            const fvMesh& mesh
        )
        :
            MeshObject
            <
                fvMesh,
                Foam::TopologicalMeshObject,
                centredCECCellToCellStencilObject
            >(mesh),
            extendedCentredCellToCellStencil(CECCellToCellStencil(mesh))
        {}


    //- Destructor
    virtual ~centredCECCellToCellStencilObject() = default;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
