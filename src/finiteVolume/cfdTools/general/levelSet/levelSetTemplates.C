/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2017 OpenFOAM Foundation
    Copyright (C) 2021 OpenCFD Ltd.
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

#include "cfdTools/general/levelSet/levelSet.H"
#include "meshes/primitiveShapes/cut/cut.H"
#include "meshes/polyMesh/polyMeshTetDecomposition/polyMeshTetDecomposition.H"
#include "meshes/polyMesh/polyMeshTetDecomposition/tetIndices.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
Foam::tmp<Foam::DimensionedField<Type, Foam::volMesh>> Foam::levelSetAverage
(
    const fvMesh& mesh,
    const scalarField& levelC,
    const scalarField& levelP,
    const DimensionedField<Type, volMesh>& positiveC,
    const DimensionedField<Type, pointMesh>& positiveP,
    const DimensionedField<Type, volMesh>& negativeC,
    const DimensionedField<Type, pointMesh>& negativeP
)
{
    tmp<DimensionedField<Type, volMesh>> tResult
    (
        new DimensionedField<Type, volMesh>
        (
            IOobject
            (
                positiveC.name() + ":levelSetAverage",
                mesh.time().timeName(),
                mesh
            ),
            mesh,
            dimensioned<Type>(positiveC.dimensions(), Zero)
        )
    );
    DimensionedField<Type, volMesh>& result = tResult.ref();

    forAll(result, cI)
    {
        const List<tetIndices> cellTetIs =
            polyMeshTetDecomposition::cellTetIndices(mesh, cI);

        scalar v = 0;
        Type r = Zero;

        forAll(cellTetIs, cellTetI)
        {
            const triFace triIs = cellTetIs[cellTetI].faceTriIs(mesh);

            const FixedList<point, 4>
                tet =
                {
                    mesh.cellCentres()[cI],
                    mesh.points()[triIs[0]],
                    mesh.points()[triIs[1]],
                    mesh.points()[triIs[2]]
                };
            const FixedList<scalar, 4>
                level =
                {
                    levelC[cI],
                    levelP[triIs[0]],
                    levelP[triIs[1]],
                    levelP[triIs[2]]
                };
            const cut::volumeIntegrateOp<Type>
                positive = FixedList<Type, 4>
                ({
                    positiveC[cI],
                    positiveP[triIs[0]],
                    positiveP[triIs[1]],
                    positiveP[triIs[2]]
                });
            const cut::volumeIntegrateOp<Type>
                negative = FixedList<Type, 4>
                ({
                    negativeC[cI],
                    negativeP[triIs[0]],
                    negativeP[triIs[1]],
                    negativeP[triIs[2]]
                });

            v += cut::volumeOp()(tet);

            r += tetCut(tet, level, positive, negative);
        }

        result[cI] = r/v;
    }

    return tResult;
}


template<class Type>
Foam::tmp<Foam::Field<Type>> Foam::levelSetAverage
(
    const fvPatch& patch,
    const scalarField& levelF,
    const scalarField& levelP,
    const Field<Type>& positiveF,
    const Field<Type>& positiveP,
    const Field<Type>& negativeF,
    const Field<Type>& negativeP
)
{
    typedef typename outerProduct<Type, vector>::type sumType;

    tmp<Field<Type>> tResult(new Field<Type>(patch.size(), Zero));
    Field<Type>& result = tResult.ref();

    forAll(result, fI)
    {
        const face& f = patch.patch().localFaces()[fI];

        vector a(Zero);
        sumType r = Zero;

        for (label edgei = 0; edgei < f.nEdges(); ++edgei)
        {
            const edge e = f.edge(edgei);

            const FixedList<point, 3>
                tri =
                {
                    patch.patch().faceCentres()[fI],
                    patch.patch().localPoints()[e[0]],
                    patch.patch().localPoints()[e[1]]
                };
            const FixedList<scalar, 3>
                level =
                {
                    levelF[fI],
                    levelP[e[0]],
                    levelP[e[1]]
                };
            const cut::areaIntegrateOp<Type>
                positive = FixedList<Type, 3>
                ({
                    positiveF[fI],
                    positiveP[e[0]],
                    positiveP[e[1]]
                });
            const cut::areaIntegrateOp<Type>
                negative = FixedList<Type, 3>
                ({
                    negativeF[fI],
                    negativeP[e[0]],
                    negativeP[e[1]]
                });

            a += cut::areaOp()(tri);

            r += triCut(tri, level, positive, negative);
        }

        result[fI] = a/magSqr(a) & r;
    }

    return tResult;
}


// ************************************************************************* //
