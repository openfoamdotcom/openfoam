/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2018 OpenFOAM Foundation
    Copyright (C) 2016-2021 OpenCFD Ltd.
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
    Foam::fvMeshDistribute

Description
    Sends/receives parts of mesh+fvfields to neighbouring processors.
    Used in load balancing.

    Input is per local cell the processor it should move to. Moves meshes
    and volFields/surfaceFields and returns map which can be used to
    distribute other.

    Notes:
    - does not handle cyclics. Will probably handle separated proc patches.
    - if all cells move off processor also all its processor patches will
      get deleted so comms might be screwed up (since e.g. globalMeshData
      expects procPatches on all)
    - initial mesh has to have procPatches last and all normal patches common
      to all processors and in the same order. This is checked.

SourceFiles
    fvMeshDistribute.C
    fvMeshDistributeTemplates.C

\*---------------------------------------------------------------------------*/

#ifndef Foam_fvMeshDistribute_H
#define Foam_fvMeshDistribute_H

#include "fields/Fields/Field/Field.H"
#include "fvMesh/fvMeshSubset/fvMeshSubset.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward Declarations
class mapAddedPolyMesh;
class mapDistributePolyMesh;

/*---------------------------------------------------------------------------*\
                      Class fvMeshDistribute Declaration
\*---------------------------------------------------------------------------*/

class fvMeshDistribute
{
    // Private Data

        //- Underlying fvMesh
        fvMesh& mesh_;


    // Private Member Functions

        static void inplaceRenumberWithFlip
        (
            const labelUList& oldToNew,
            const bool oldToNewHasFlip,
            const bool lstHasFlip,
            labelUList& lst
        );

        //- Find indices with value
        static labelList select
        (
            const bool selectEqual,
            const labelList& values,
            const label value
        );

        //- Merge wordlists over all processors
        static wordList mergeWordList(const wordList&);

        //- Reorder zones according to names
        template<class ZoneType, class ZoneMesh>
        void reorderZones
        (
            const wordList& zoneNames,
            ZoneMesh& zones
        );


        // Patch handling

            //- Find patch to put exposed faces into.
            label findNonEmptyPatch() const;

            //- Save boundary fields
            template<class T, class Mesh>
            void saveBoundaryFields
            (
                PtrList<FieldField<fvsPatchField, T>>& bflds
            ) const;

            //- Map boundary fields
            template<class T, class Mesh>
            void mapBoundaryFields
            (
                const mapPolyMesh& map,
                const PtrList<FieldField<fvsPatchField, T>>& oldBflds
            );

            //- Save internal fields of surfaceFields
            template<class T>
            void saveInternalFields(PtrList<Field<T>>& iflds) const;

            //- Set value of patch faces resulting from internal faces
            template<class T>
            void mapExposedFaces
            (
                const mapPolyMesh& map,
                const PtrList<Field<T>>& oldFlds
            );

            //- Init patch fields of certain type
            template<class GeoField, class PatchFieldType>
            void initPatchFields
            (
                const typename GeoField::value_type& initVal
            );

            ////- Call correctBoundaryConditions on fields
            //template<class GeoField>
            //void correctBoundaryConditions();

            //- Delete all processor patches. Move any processor faces into
            //  patchi.
            autoPtr<mapPolyMesh> deleteProcPatches(const label patchi);

            //- Repatch the mesh. This is only necessary for the proc
            //  boundary faces. newPatchID is over all boundary faces: -1 or
            //  new patchID. constructFaceMap is being adapted for the
            //  possible new face position (since proc faces get automatically
            //  matched)
            autoPtr<mapPolyMesh> repatch
            (
                const labelList& newPatchID,
                labelListList& constructFaceMap
            );

            //- Merge any local points that were remotely coupled.
            //  constructPointMap is adapted for the new point labels.
            autoPtr<mapPolyMesh> mergeSharedPoints
            (
                const labelList& pointToGlobalMaster,
                labelListList& constructPointMap
            );


        // Coupling information

            //- Construct the local environment of all boundary faces.
            void getCouplingData
            (
                const labelList& distribution,
                labelList& sourceFace,
                labelList& sourceProc,
                labelList& sourcePatch,
                labelList& sourceNewProc,
                labelList& sourcePointMaster
            ) const;

            // Subset the neighbourCell/neighbourProc fields
            static void subsetCouplingData
            (
                const fvMesh& mesh,
                const labelList& pointMap,
                const labelList& faceMap,
                const labelList& cellMap,

                const labelList& oldDistribution,
                const labelList& oldFaceOwner,
                const labelList& oldFaceNeighbour,
                const label oldInternalFaces,

                const labelList& sourceFace,
                const labelList& sourceProc,
                const labelList& sourcePatch,
                const labelList& sourceNewProc,
                const labelList& sourcePointMaster,

                labelList& subFace,
                labelList& subProc,
                labelList& subPatch,
                labelList& subNewProc,
                labelList& subPointMaster
            );

            //- Find cells on mesh whose faceID/procID match the neighbour
            //  cell/proc of domainMesh. Store the matching face.
            static void findCouples
            (
                const primitiveMesh&,
                const labelList& sourceFace,
                const labelList& sourceProc,
                const labelList& sourcePatch,

                const label domain,
                const primitiveMesh& domainMesh,
                const labelList& domainFace,
                const labelList& domainProc,
                const labelList& domainPatch,

                labelList& masterCoupledFaces,
                labelList& slaveCoupledFaces
            );

            //- Find cells on mesh whose faceID/procID match the neighbour
            //  cell/proc of domainMesh. Store the matching face pairs
            static void findCouples
            (
                const UPtrList<polyMesh>& meshes,
                const PtrList<labelList>& domainSourceFaces,
                const PtrList<labelList>& domainSourceProcs,
                const PtrList<labelList>& domainSourcePatchs,

                labelListList& localBoundaryFace,
                labelListList& remoteFaceProc,
                labelListList& remoteBoundaryFace
            );

            //- Map data on boundary faces to new mesh (resulting from adding
            //  two meshes)
            static labelList mapBoundaryData
            (
                const primitiveMesh& mesh,      // mesh after adding
                const mapAddedPolyMesh& map,
                const labelList& boundaryData0, // mesh before adding
                const label nInternalFaces1,
                const labelList& boundaryData1  // added mesh
            );

            //- Map point data to new mesh (resulting from adding two meshes)
            static labelList mapPointData
            (
                const primitiveMesh& mesh,      // mesh after adding
                const mapAddedPolyMesh& map,
                const labelList& boundaryData0, // on mesh before adding
                const labelList& boundaryData1  // on added mesh
            );

        // Other

            //- Remove cells. Add all exposed faces to patch oldInternalPatchi
            autoPtr<mapPolyMesh> doRemoveCells
            (
                const labelList& cellsToRemove,
                const label oldInternalPatchi
            );

            //- Add processor patches. Changes mesh and returns per neighbour
            //  proc the processor patchID.
            void addProcPatches
            (
                const labelList&, // processor that neighbour is now on
                const labelList&, // -1 or patch that face originated from
                List<Map<label>>& procPatchID
            );

            //- Get boundary faces to be repatched. Is -1 or new patchID
            static labelList getBoundaryPatch
            (
                const labelList& neighbourNewProc,  // new processor per b. face
                const labelList& referPatchID,      // -1 or original patch
                const List<Map<label>>& procPatchID // patchID
            );

            //- Send mesh and coupling data.
            static void sendMesh
            (
                const label domain,
                const fvMesh& mesh,
                const wordList& pointZoneNames,
                const wordList& facesZoneNames,
                const wordList& cellZoneNames,
                const labelList& sourceFace,
                const labelList& sourceProc,
                const labelList& sourcePatch,
                const labelList& sourceNewProc,
                const labelList& sourcePointMaster,
                Ostream& toDomain
            );

            //- Get sorted names of GeoField, optionally test
            //- that all procs have the same names.
            template<class GeoField>
            static void getFieldNames
            (
                const fvMesh& mesh,
                HashTable<wordList>& allFieldNames,
                const word& excludeType = word::null,
                const bool syncPar = true
            );

            //- Send subset of fields
            template<class GeoField>
            static void sendFields
            (
                const label domain,
                const HashTable<wordList>& allFieldNames,
                const fvMeshSubset& subsetter,
                Ostream&
            );

            //- Receive mesh. Opposite of sendMesh
            static autoPtr<fvMesh> receiveMesh
            (
                const label domain,
                const wordList& pointZoneNames,
                const wordList& facesZoneNames,
                const wordList& cellZoneNames,
                const Time& runTime,
                labelList& domainSourceFace,
                labelList& domainSourceProc,
                labelList& domainSourcePatch,
                labelList& domainSourceNewProc,
                labelList& domainSourcePointMaster,
                Istream& fromNbr
            );

            //- Receive fields. Opposite of sendFields
            template<class GeoField>
            static void receiveFields
            (
                const label domain,
                const HashTable<wordList>& allFieldNames,
                fvMesh& mesh,
                PtrList<GeoField>& fields,
                const dictionary& allFieldsDict
            );

            //- No copy construct
            fvMeshDistribute(const fvMeshDistribute&) = delete;

            //- No copy assignment
            void operator=(const fvMeshDistribute&) = delete;

public:

    ClassName("fvMeshDistribute");


    // Constructors

        //- Construct from mesh
        explicit fvMeshDistribute(fvMesh& mesh);


    // Member Functions

        //- Helper function: count cells per processor in wanted distribution
        static labelList countCells(const labelList&);

        //- Send cells to neighbours according to distribution
        //  (for every cell the new proc)
        autoPtr<mapDistributePolyMesh> distribute(const labelList& dist);

        // Debugging

            //- Print some info on coupling data
            static void printCoupleInfo
            (
                const primitiveMesh&,
                const labelList&,
                const labelList&,
                const labelList&,
                const labelList&
            );

            //- Print some field info
            template<class GeoField>
            static void printIntFieldInfo(const fvMesh&);

            //- Print some field info
            template<class GeoField>
            static void printFieldInfo(const fvMesh&);

            //- Print some info on mesh.
            static void printMeshInfo(const polyMesh&);

            //- Generate a test field on faces
            static tmp<surfaceScalarField> generateTestField(const fvMesh&);

            //- Check whether field consistent with face orientation
            static void testField(const surfaceScalarField&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "fvMeshDistribute/fvMeshDistributeTemplates.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
