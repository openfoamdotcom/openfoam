/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016 OpenFOAM Foundation
    Copyright (C) 2020-2022 OpenCFD Ltd.
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
    Foam::OppositeFaceCellWave

Description
    Version of FaceCellWave that walks through prismatic cells only.

    Used to determine mesh structure. In the front walking routines
    (faceToCell and faceToCell) it
    - walks across prismatic cells only
    - and only to a single opposite face

    Notes:
    A cell with a split faces will be marked but not walked through (since
    there is no single opposite face.

SourceFiles
    OppositeFaceCellWave.C

\*---------------------------------------------------------------------------*/

#ifndef Foam_OppositeFaceCellWave_H
#define Foam_OppositeFaceCellWave_H

#include "algorithms/MeshWave/FaceCellWave.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                  Class OppositeFaceCellWaveBase Declaration
\*---------------------------------------------------------------------------*/

class OppositeFaceCellWaveBase
{
protected:

    // Protected Data

        //- For every entry in changedCells (i.e. the cell front) gives
        //  the face that it needs to transfer to
        DynamicList<label> changedOppositeFaces_;


public:

    //- Runtime type information
    ClassName("OppositeFaceCellWave");


    // Constructors

        //- Construct with mesh reference (for sizing)
        OppositeFaceCellWaveBase(const polyMesh& mesh);
};


/*---------------------------------------------------------------------------*\
                    Class OppositeFaceCellWave Declaration
\*---------------------------------------------------------------------------*/

template<class Type, class TrackingData = int>
class OppositeFaceCellWave
:
    public FaceCellWave<Type, TrackingData>,
    public OppositeFaceCellWaveBase
{
protected:

   // Protected Member Functions

        //- Determine 'opposite' faces (= faces not sharing a vertex) on cell
        void opposingFaceLabels
        (
            const label celli,
            const label facei,
            DynamicList<label>&
        ) const;


public:

    // Constructors

        //- Construct from mesh and list of changed faces with the Type
        //- for these faces.
        //  Iterates until nothing changes or maxIter reached.
        //  (maxIter can be 0)
        OppositeFaceCellWave
        (
            const polyMesh&,
            const labelList& initialChangedFaces,
            const List<Type>& changedFacesInfo,
            UList<Type>& allFaceInfo,
            UList<Type>& allCellInfo,
            const label maxIter,
            TrackingData& td = FaceCellWaveBase::dummyTrackData_
        );


    //- Destructor
    virtual ~OppositeFaceCellWave() = default;


    // Member Functions

        //- Propagate from face to cell. Returns total number of cells
        //  (over all processors) changed.
        virtual label faceToCell();

        //- Propagate from cell to face. Returns total number of faces
        //  (over all processors) changed. (Faces on processorpatches are
        //  counted double)
        virtual label cellToFace();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "structuredRenumber/OppositeFaceCellWave.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
