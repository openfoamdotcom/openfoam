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
    Foam::extendedUpwindCellToFaceStencil

Description
    Creates upwind stencil by shifting a centred stencil to upwind and downwind
    faces and optionally removing all non-(up/down)wind faces ('pureUpwind').

    Note: the minOpposedness parameter is to decide which upwind and
    downwind faces to combine the stencils from. If myArea is the
    local area and upwindArea
    the area of the possible upwind candidate it will be included if
        (upwindArea & myArea)/magSqr(myArea) > minOpposedness
    so this includes both cosine and area. WIP.

SourceFiles
    extendedUpwindCellToFaceStencil.C
    extendedUpwindCellToFaceStencilTemplates.C

\*---------------------------------------------------------------------------*/

#ifndef extendedUpwindCellToFaceStencil_H
#define extendedUpwindCellToFaceStencil_H

#include "fvMesh/extendedStencil/cellToFace/extendedCellToFaceStencil.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class cellToFaceStencil;

/*---------------------------------------------------------------------------*\
               Class extendedUpwindCellToFaceStencil Declaration
\*---------------------------------------------------------------------------*/

class extendedUpwindCellToFaceStencil
:
    public extendedCellToFaceStencil
{
    // Private data

        //- Does stencil contain upwind points only
        const bool pureUpwind_;

        //- Swap map for getting neighbouring data
        autoPtr<mapDistribute> ownMapPtr_;
        autoPtr<mapDistribute> neiMapPtr_;

        //- Per face the stencil.
        labelListList ownStencil_;
        labelListList neiStencil_;



    // Private Member Functions

        //- Find most 'opposite' faces of cell
        void selectOppositeFaces
        (
            const boolList& nonEmptyFace,
            const scalar minOpposedness,
            const label facei,
            const label celli,
            DynamicList<label>& oppositeFaces
        ) const;

        //- Transport (centred) face stencil to 'opposite' face.
        void transportStencil
        (
            const boolList& nonEmptyFace,
            const labelListList& faceStencil,
            const scalar minOpposedness,
            const label facei,
            const label celli,
            const bool stencilHasNeighbour,

            DynamicList<label>& oppositeFaces,
            labelHashSet& faceStencilSet,
            labelList& transportedStencil
        ) const;

        //- Transport (centred) face stencil to 'opposite' faces.
        void transportStencils
        (
            const labelListList& faceStencil,
            const scalar minOpposedness,
            labelListList& ownStencil,
            labelListList& neiStencil
        );


        //- No copy construct
        extendedUpwindCellToFaceStencil
        (
            const extendedUpwindCellToFaceStencil&
        ) = delete;

        //- No copy assignment
        void operator=(const extendedUpwindCellToFaceStencil&) = delete;


public:

    // Constructors

        //- Construct from mesh and uncompacted centred face stencil.
        //  Transports facestencil to create owner and neighbour versions.
        //  pureUpwind to remove any remaining downwind cells.
        extendedUpwindCellToFaceStencil
        (
            const cellToFaceStencil&,
            const bool pureUpwind,
            const scalar minOpposedness
        );

        //- Construct from mesh and uncompacted centred face stencil. Splits
        //  stencil into owner and neighbour (so always pure upwind)
        extendedUpwindCellToFaceStencil
        (
            const cellToFaceStencil&
        );


    // Member Functions

        bool pureUpwind() const
        {
            return pureUpwind_;
        }

        //- Return reference to the parallel distribution map
        const mapDistribute& ownMap() const
        {
            return *ownMapPtr_;
        }

        //- Return reference to the parallel distribution map
        const mapDistribute& neiMap() const
        {
            return *neiMapPtr_;
        }

        //- Return reference to the stencil
        const labelListList& ownStencil() const
        {
            return ownStencil_;
        }

        //- Return reference to the stencil
        const labelListList& neiStencil() const
        {
            return neiStencil_;
        }

        //- Sum vol field contributions to create face values
        template<class Type>
        tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> weightedSum
        (
            const surfaceScalarField& phi,
            const GeometricField<Type, fvPatchField, volMesh>& fld,
            const List<List<scalar>>& ownWeights,
            const List<List<scalar>>& neiWeights
        ) const;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "fvMesh/extendedStencil/cellToFace/extendedUpwindCellToFaceStencilTemplates.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
