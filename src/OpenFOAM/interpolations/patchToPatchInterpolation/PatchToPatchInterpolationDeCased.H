/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2022 OpenCFD Ltd.
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
    Foam::PatchToPatchInterpolation

Description
    Interpolation class dealing with transfer of data between two
    primitivePatches

SourceFiles
    PatchToPatchInterpolation.C
    PatchToPatchInterpolate.C
    CalcPatchToPatchWeights.C

\*---------------------------------------------------------------------------*/

#ifndef Foam_PatchToPatchInterpolation_H
#define Foam_PatchToPatchInterpolation_H

#include "db/typeInfo/className.H"
#include "primitives/ints/lists/labelList.H"
#include "fields/Fields/scalarField/scalarField.H"
#include "meshes/primitiveShapes/point/pointField.H"
#include "fields/FieldFields/FieldField/FieldFields.H"
#include "meshes/meshShapes/face/faceList.H"
#include "meshes/primitiveShapes/triangle/intersection.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                Class PatchToPatchInterpolationBase Declaration
\*---------------------------------------------------------------------------*/

class PatchToPatchInterpolationBase
{
protected:

    // Protected Static Data

        //- Relative merge tolerance for projected points missing the target
        //  Expressed as the fraction of min involved edge size
        static scalar projectionTol_;

        //- Direct hit tolerance
        static const scalar directHitTol;


public:

    //- Runtime type information
    ClassName("PatchToPatchInterpolation");


    // Constructors

        //- Default construct
        PatchToPatchInterpolationBase() noexcept = default;


    // Member Functions

        //- Access to projection tolerance
        static scalar projectionTol() noexcept
        {
            return projectionTol_;
        }

        //- Change propagation tolerance, return previous value
        static scalar setProjectionTol(const scalar tol)
        {
            if (tol < -VSMALL)
            {
                FatalErrorInFunction << abort(FatalError);
            }
            scalar old(projectionTol_);
            projectionTol_ = tol;
            return old;
        }
};


/*---------------------------------------------------------------------------*\
                  Class PatchToPatchInterpolation Declaration
\*---------------------------------------------------------------------------*/

template<class FromPatch, class ToPatch>
class PatchToPatchInterpolation
:
    public PatchToPatchInterpolationBase
{
    // Private Data

        //- Reference to the source patch
        const FromPatch& fromPatch_;

        //- Reference to the target patch
        const ToPatch& toPatch_;

        //- Type of intersection algorithm to use in projection
        intersection::algorithm alg_;

        //- Direction projection to use in projection
        intersection::direction dir_;


    // Point Addressing

        //- Face into which each point of target patch is projected
        mutable std::unique_ptr<labelList> pointAddressingPtr_;

        //- Weighting factors
        mutable std::unique_ptr<FieldField<Field, scalar>> pointWeightsPtr_;

        //- Distance to intersection for patch points
        mutable std::unique_ptr<scalarField> pointDistancePtr_;


    // Face Addressing

        //- Face into which each face centre of target patch is projected
        mutable std::unique_ptr<labelList> faceAddressingPtr_;

        //- Weighting factors
        mutable std::unique_ptr<FieldField<Field, scalar>> faceWeightsPtr_;

        //- Distance to intersection for patch face centres
        mutable std::unique_ptr<scalarField> faceDistancePtr_;


    // Private Member Functions

        //- No copy construct
        PatchToPatchInterpolation(const PatchToPatchInterpolation&) = delete;

        //- No copy assignment
        void operator=(const PatchToPatchInterpolation&) = delete;

        //- Calculate point weights
        void calcPointAddressing() const;

        //- Calculate face weights
        void calcFaceAddressing() const;

        //- Clear all geometry and addressing
        void clearOut();


        //- Return reference to point addressing
        const labelList& pointAddr() const;

        //- Return reference to point weights
        const FieldField<Field, scalar>& pointWeights() const;

        //- Return reference to face addressing
        const labelList& faceAddr() const;

        //- Return reference to face weights
        const FieldField<Field, scalar>& faceWeights() const;


public:

    // Constructors

        //- Construct from components
        PatchToPatchInterpolation
        (
            const FromPatch& fromPatch,
            const ToPatch& toPatch,
            const intersection::algorithm alg = intersection::FULL_RAY,
            const intersection::direction dir = intersection::VECTOR
        );


    //- Destructor
    ~PatchToPatchInterpolation();


    // Member Functions

        //- Return ype of intersection algorithm to use in projection
        intersection::algorithm projectionAlgo() const
        {
            return alg_;
        }

        //- Return direction projection to use in projection
        intersection::direction projectionDir() const
        {
            return dir_;
        }

        //- Return distance to intersection for patch points
        const scalarField& pointDistanceToIntersection() const;

        //- Return distance to intersection for patch face centres
        const scalarField& faceDistanceToIntersection() const;

        //- Correct weighting factors for moving mesh.
        bool movePoints();


        //- Interpolate point field
        template<class Type>
        tmp<Field<Type>> pointInterpolate(const Field<Type>& pf) const;

        template<class Type>
        tmp<Field<Type>> pointInterpolate(const tmp<Field<Type>>& tpf) const;

        //- Interpolate face field
        template<class Type>
        tmp<Field<Type>> faceInterpolate(const Field<Type>& pf) const;

        template<class Type>
        tmp<Field<Type>> faceInterpolate(const tmp<Field<Type>>& tpf) const;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

#ifdef NoRepository
    #include "interpolations/patchToPatchInterpolation/PatchToPatchInterpolation.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
