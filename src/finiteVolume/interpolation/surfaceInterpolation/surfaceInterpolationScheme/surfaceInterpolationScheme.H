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
    Foam::surfaceInterpolationScheme

Description
    Abstract base class for surface interpolation schemes.

SourceFiles
    surfaceInterpolationScheme.C

\*---------------------------------------------------------------------------*/

#ifndef surfaceInterpolationScheme_H
#define surfaceInterpolationScheme_H

#include "memory/tmp/tmp.H"
#include "fields/volFields/volFieldsFwd.H"
#include "fields/surfaceFields/surfaceFieldsFwd.H"
#include "db/typeInfo/typeInfo.H"
#include "db/runTimeSelection/construction/runTimeSelectionTables.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class fvMesh;

/*---------------------------------------------------------------------------*\
                 Class surfaceInterpolationScheme Declaration
\*---------------------------------------------------------------------------*/

template<class Type>
class surfaceInterpolationScheme
:
    public refCount
{
    // Private data

        //- Hold reference to mesh
        const fvMesh& mesh_;


    // Private Member Functions

        //- No copy construct
        surfaceInterpolationScheme(const surfaceInterpolationScheme&) = delete;

        //- No copy assignment
        void operator=(const surfaceInterpolationScheme&) = delete;


public:

    //- Runtime type information
    TypeName("surfaceInterpolationScheme");


    // Declare run-time constructor selection tables

        declareRunTimeSelectionTable
        (
            tmp,
            surfaceInterpolationScheme,
            Mesh,
            (
                const fvMesh& mesh,
                Istream& schemeData
            ),
            (mesh, schemeData)
        );

        declareRunTimeSelectionTable
        (
            tmp,
            surfaceInterpolationScheme,
            MeshFlux,
            (
                const fvMesh& mesh,
                const surfaceScalarField& faceFlux,
                Istream& schemeData
            ),
            (mesh, faceFlux, schemeData)
        );


    // Constructors

        //- Construct from mesh
        surfaceInterpolationScheme(const fvMesh& mesh)
        :
            mesh_(mesh)
        {}


    // Selectors

        //- Return new tmp interpolation scheme
        static tmp<surfaceInterpolationScheme<Type>> New
        (
            const fvMesh& mesh,
            Istream& schemeData
        );

        //- Return new tmp interpolation scheme
        static tmp<surfaceInterpolationScheme<Type>> New
        (
            const fvMesh& mesh,
            const surfaceScalarField& faceFlux,
            Istream& schemeData
        );


    //- Destructor
    virtual ~surfaceInterpolationScheme() = default;


    // Member Functions

        //- Return mesh reference
        const fvMesh& mesh() const
        {
            return mesh_;
        }


        //- Return the face-interpolate of the given cell field
        //  with the given owner and neighbour weighting factors
        static tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
        interpolate
        (
            const GeometricField<Type, fvPatchField, volMesh>&,
            const tmp<surfaceScalarField>&,
            const tmp<surfaceScalarField>&
        );

        //- Return the face-interpolate of the given cell field
        //  with the given weighting factors dotted with given field Sf
        template<class SFType>
        static tmp
        <
            GeometricField
            <
                typename innerProduct<typename SFType::value_type, Type>::type,
                fvsPatchField,
                surfaceMesh
            >
        >
        dotInterpolate
        (
            const SFType& Sf,
            const GeometricField<Type, fvPatchField, volMesh>& vf,
            const tmp<surfaceScalarField>& tlambdas
        );

        //- Return the face-interpolate of the given cell field
        //  with the given weighting factors
        static tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
        interpolate
        (
            const GeometricField<Type, fvPatchField, volMesh>&,
            const tmp<surfaceScalarField>&
        );

        //- Return the interpolation weighting factors for the given field
        virtual tmp<surfaceScalarField> weights
        (
            const GeometricField<Type, fvPatchField, volMesh>&
        ) const = 0;

        //- Return true if this scheme uses an explicit correction
        virtual bool corrected() const
        {
            return false;
        }

        //- Return the explicit correction to the face-interpolate
        //  for the given field
        virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
        correction(const GeometricField<Type, fvPatchField, volMesh>&) const
        {
            return nullptr;
        }

        //- Return the face-interpolate of the given cell field
        //  with explicit correction dotted with given field Sf
        virtual
        tmp
        <
            GeometricField
            <
                typename innerProduct<vector, Type>::type,
                fvsPatchField,
                surfaceMesh
            >
        >
        dotInterpolate
        (
            const surfaceVectorField& Sf,
            const GeometricField<Type, fvPatchField, volMesh>& vf
        ) const;

        //- Return the face-interpolate of the given tmp cell field
        //  with explicit correction dotted with given field Sf
        tmp
        <
            GeometricField
            <
                typename innerProduct<vector, Type>::type,
                fvsPatchField,
                surfaceMesh
            >
        >
        dotInterpolate
        (
            const surfaceVectorField& Sf,
            const tmp<GeometricField<Type, fvPatchField, volMesh>>&
        ) const;

        //- Return the face-interpolate of the given cell field
        //  with explicit correction
        virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
        interpolate(const GeometricField<Type, fvPatchField, volMesh>&) const;

        //- Return the face-interpolate of the given tmp cell field
        //  with explicit correction
        tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
        interpolate
        (
            const tmp<GeometricField<Type, fvPatchField, volMesh>>&
        ) const;
};


template<>
tmp
<
    GeometricField
    <
        typename innerProduct<vector, scalar>::type,
        fvsPatchField,
        surfaceMesh
    >
>
surfaceInterpolationScheme<scalar>::dotInterpolate
(
    const surfaceVectorField& Sf,
    const GeometricField<scalar, fvPatchField, volMesh>&
) const;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Add the patch constructor functions to the hash tables

#define makeSurfaceInterpolationTypeScheme(SS, Type)                           \
                                                                               \
defineNamedTemplateTypeNameAndDebug(SS<Type>, 0);                              \
                                                                               \
surfaceInterpolationScheme<Type>::addMeshConstructorToTable<SS<Type>>          \
    add##SS##Type##MeshConstructorToTable_;                                    \
                                                                               \
surfaceInterpolationScheme<Type>::addMeshFluxConstructorToTable<SS<Type>>      \
    add##SS##Type##MeshFluxConstructorToTable_;

#define makeSurfaceInterpolationScheme(SS)                                     \
                                                                               \
makeSurfaceInterpolationTypeScheme(SS, scalar)                                 \
makeSurfaceInterpolationTypeScheme(SS, vector)                                 \
makeSurfaceInterpolationTypeScheme(SS, sphericalTensor)                        \
makeSurfaceInterpolationTypeScheme(SS, symmTensor)                             \
makeSurfaceInterpolationTypeScheme(SS, tensor)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "interpolation/surfaceInterpolation/surfaceInterpolationScheme/surfaceInterpolationScheme.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
