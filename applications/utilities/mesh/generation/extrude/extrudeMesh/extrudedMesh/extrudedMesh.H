/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2015 OpenFOAM Foundation
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

Class
    Foam::extrudedMesh

Description

SourceFiles
    extrudedMesh.C
    extrudedMeshTemplates.C

\*---------------------------------------------------------------------------*/

#ifndef extrudedMesh_H
#define extrudedMesh_H

#include "meshes/polyMesh/polyMesh.H"
#include "extrudeModel/extrudeModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class extrudedMesh Declaration
\*---------------------------------------------------------------------------*/

class extrudedMesh
:
    public polyMesh
{
    // Private Data

        const extrudeModel& model_;


    // Private Member Functions

        //- Do edge and face use points in same order?
        static bool sameOrder(const face&, const edge&);

        //- Construct and return the extruded mesh points
        template<class FaceList, class PointField>
        pointField extrudedPoints
        (
            const PrimitivePatch<FaceList, PointField>& extrudePatch,
            const extrudeModel&
        );

        //- Construct and return the extruded mesh faces
        template<class FaceList, class PointField>
        faceList extrudedFaces
        (
            const PrimitivePatch<FaceList, PointField>& extrudePatch,
            const extrudeModel&
        );

        //- Construct and return the extruded mesh cells
        template<class FaceList, class PointField>
        cellList extrudedCells
        (
            const PrimitivePatch<FaceList, PointField>& extrudePatch,
            const extrudeModel&
        );


        //- No copy construct
        extrudedMesh(const extrudedMesh&) = delete;

        //- No copy assignment
        void operator=(const extrudedMesh&) = delete;


public:

    // Constructors

        //- Construct from the primitivePatch to extrude
        template<class FaceList, class PointField>
        extrudedMesh
        (
            const IOobject&,
            const PrimitivePatch<FaceList, PointField>& extrudePatch,
            const extrudeModel&
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "extrudedMesh/extrudedMeshTemplates.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
