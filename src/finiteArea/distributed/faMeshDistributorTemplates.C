/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2022-2023 OpenCFD Ltd.
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

#include "db/Time/TimeOpenFOAM.H"
#include "fields/faPatchFields/constraint/empty/emptyFaPatchField.H"
#include "fields/faePatchFields/constraint/empty/emptyFaePatchField.H"
#include "db/IOobjectList/IOobjectList.H"
#include "meshes/polyMesh/polyMesh.H"
#include "meshes/polyMesh/polyPatches/polyPatch/polyPatch.H"
#include "faMesh/faPatches/constraint/processor/processorFaPatch.H"
#include "meshes/polyMesh/mapPolyMesh/mapDistribute/mapDistribute.H"
#include "meshes/polyMesh/mapPolyMesh/mapDistribute/mapDistributePolyMesh.H"
#include "fields/areaFields/areaFields.H"
#include "fields/edgeFields/edgeFields.H"

#include "fields/Fields/Field/distributedFieldMapper.H"
#include "fields/faPatchFields/faPatchField/distributedFaPatchFieldMapper.H"

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
Foam::tmp<Foam::GeometricField<Type, Foam::faPatchField, Foam::areaMesh>>
Foam::faMeshDistributor::distributeField
(
    const GeometricField<Type, faPatchField, areaMesh>& fld
) const
{
    typedef typename
        GeometricField<Type, faPatchField, areaMesh>::Patch
        PatchFieldType;

    if (tgtMesh_.boundary().size() && patchEdgeMaps_.empty())
    {
        createPatchMaps();
    }

    // Create internalField by remote mapping

    const distributedFieldMapper mapper
    (
        labelUList::null(),
        distMap_.cellMap()  // area: faceMap (volume: cellMap)
    );

    DimensionedField<Type, areaMesh> internalField
    (
        IOobject
        (
            fld.name(),
            tgtMesh_.time().timeName(),
            fld.local(),
            tgtMesh_.thisDb(),
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        tgtMesh_,
        fld.dimensions(),
        Field<Type>(fld.internalField(), mapper)
    );

    internalField.oriented() = fld.oriented();


    // Create patchFields by remote mapping

    PtrList<PatchFieldType> newPatchFields(tgtMesh_.boundary().size());

    const auto& bfld = fld.boundaryField();

    forAll(bfld, patchi)
    {
        if (patchEdgeMaps_.test(patchi))
        {
            // Clone local patch field

            const distributedFaPatchFieldMapper mapper
            (
                labelUList::null(),
                patchEdgeMaps_[patchi]
            );

            // Map into local copy
            newPatchFields.set
            (
                patchi,
                PatchFieldType::New
                (
                    bfld[patchi],
                    tgtMesh_.boundary()[patchi],
                    DimensionedField<Type, areaMesh>::null(),
                    mapper
                )
            );
        }
    }

    // Add empty patchFields on remaining patches (this also handles
    // e.g. processorPatchFields or any other constraint type patches)
    forAll(newPatchFields, patchi)
    {
        if (!newPatchFields.set(patchi))
        {
            newPatchFields.set
            (
                patchi,
                PatchFieldType::New
                (
                    emptyFaPatchField<Type>::typeName,
                    tgtMesh_.boundary()[patchi],
                    DimensionedField<Type, areaMesh>::null()
                )
            );
        }
    }


    auto tresult = tmp<GeometricField<Type, faPatchField, areaMesh>>::New
    (
        std::move(internalField),
        newPatchFields
    );
    auto& result = tresult.ref();

    result.boundaryFieldRef().template evaluateCoupled<processorFaPatch>();

    return tresult;
}


template<class Type>
Foam::tmp<Foam::GeometricField<Type, Foam::faePatchField, Foam::edgeMesh>>
Foam::faMeshDistributor::distributeField
(
    const GeometricField<Type, faePatchField, edgeMesh>& fld
) const
{
    typedef typename
        GeometricField<Type, faePatchField, edgeMesh>::Patch
        PatchFieldType;

    if (!internalEdgeMap_)
    {
        createInternalEdgeMap();
    }


    // Create internalField by remote mapping

    const distributedFieldMapper mapper
    (
        labelUList::null(),
        *(internalEdgeMap_)
    );

    DimensionedField<Type, edgeMesh> internalField
    (
        IOobject
        (
            fld.name(),
            tgtMesh_.time().timeName(),
            fld.local(),
            tgtMesh_.thisDb(),
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        tgtMesh_,
        fld.dimensions(),
        Field<Type>(fld.internalField(), mapper)
    );

    internalField.oriented() = fld.oriented();


    // Create patchFields by remote mapping

    PtrList<PatchFieldType> newPatchFields(tgtMesh_.boundary().size());

    const auto& bfld = fld.boundaryField();

    forAll(bfld, patchi)
    {
        if (patchEdgeMaps_.test(patchi))
        {
            // Clone local patch field

            const distributedFaPatchFieldMapper mapper
            (
                labelUList::null(),
                patchEdgeMaps_[patchi]
            );

            // Map into local copy
            newPatchFields.set
            (
                patchi,
                PatchFieldType::New
                (
                    bfld[patchi],
                    tgtMesh_.boundary()[patchi],
                    DimensionedField<Type, edgeMesh>::null(),
                    mapper
                )
            );
        }
    }

    // Add empty patchFields on remaining patches (this also handles
    // e.g. processorPatchFields or any other constraint type patches)
    forAll(newPatchFields, patchi)
    {
        if (!newPatchFields.set(patchi))
        {
            newPatchFields.set
            (
                patchi,
                PatchFieldType::New
                (
                    emptyFaePatchField<Type>::typeName,
                    tgtMesh_.boundary()[patchi],
                    DimensionedField<Type, edgeMesh>::null()
                )
            );
        }
    }


    return tmp<GeometricField<Type, faePatchField, edgeMesh>>::New
    (
        std::move(internalField),
        newPatchFields
    );
}


template<class Type>
Foam::tmp<Foam::GeometricField<Type, Foam::faPatchField, Foam::areaMesh>>
Foam::faMeshDistributor::distributeAreaField
(
    const IOobject& fieldObject
) const
{
    // Read field
    GeometricField<Type, faPatchField, areaMesh> fld
    (
        fieldObject,
        srcMesh_
    );

    // Redistribute
    return distributeField(fld);
}


template<class Type>
Foam::tmp<Foam::GeometricField<Type, Foam::faePatchField, Foam::edgeMesh>>
Foam::faMeshDistributor::distributeEdgeField
(
    const IOobject& fieldObject
) const
{
    // Read field
    GeometricField<Type, faePatchField, edgeMesh> fld
    (
        fieldObject,
        srcMesh_
    );

    // Redistribute
    return distributeField(fld);
}


template<class Type>
Foam::label Foam::faMeshDistributor::distributeAreaFields
(
    const IOobjectList& objects,
    const wordRes& selectedFields
) const
{
    typedef GeometricField<Type, faPatchField, areaMesh> fieldType;

    label nFields = 0;

    for
    (
        const IOobject& io :
        (
            selectedFields.empty()
          ? objects.csorted<fieldType>()
          : objects.csorted<fieldType>(selectedFields)
        )
    )
    {
        if (verbose_)
        {
            if (!nFields)
            {
                Info<< "    Reconstructing "
                    << fieldType::typeName << "s\n" << nl;
            }
            Info<< "        " << io.name() << nl;
        }
        ++nFields;

        tmp<fieldType> tfld(distributeAreaField<Type>(io));

        if (isWriteProc_.good())
        {
            if (isWriteProc_)
            {
                tfld().write();
            }
        }
        else if (writeHandler_ && writeHandler_->good())
        {
            auto oldHandler = fileOperation::fileHandler(writeHandler_);
            const label oldComm = UPstream::commWorld(fileHandler().comm());

            tfld().write();

            writeHandler_ = fileOperation::fileHandler(oldHandler);
            UPstream::commWorld(oldComm);
        }
    }

    if (nFields && verbose_) Info<< endl;
    return nFields;
}


template<class Type>
Foam::label Foam::faMeshDistributor::distributeEdgeFields
(
    const IOobjectList& objects,
    const wordRes& selectedFields
) const
{
    typedef GeometricField<Type, faePatchField, edgeMesh> fieldType;

    label nFields = 0;

    for
    (
        const IOobject& io :
        (
            selectedFields.empty()
          ? objects.csorted<fieldType>()
          : objects.csorted<fieldType>(selectedFields)
        )
    )
    {
        if (verbose_)
        {
            if (!nFields)
            {
                Info<< "    Reconstructing "
                    << fieldType::typeName << "s\n" << nl;
            }
            Info<< "        " << io.name() << nl;
        }
        ++nFields;

        tmp<fieldType> tfld(distributeEdgeField<Type>(io));
        if (isWriteProc_.good())
        {
            if (isWriteProc_)
            {
                tfld().write();
            }
        }
        else if (writeHandler_ && writeHandler_->good())
        {
            auto oldHandler = fileOperation::fileHandler(writeHandler_);
            const label oldComm = UPstream::commWorld(fileHandler().comm());

            tfld().write();

            writeHandler_ = fileOperation::fileHandler(oldHandler);
            UPstream::commWorld(oldComm);
        }
    }

    if (nFields && verbose_) Info<< endl;
    return nFields;
}



#if 0
template<class Type>
void Foam::faMeshDistributor::redistributeAndWrite
(
    PtrList<GeometricField<Type, faPatchField, areaMesh>>& flds
) const
{
    for (auto& fld : flds)
    {
        Pout<< "process: " << fld.name() << endl;

        tmp<GeometricField<Type, faPatchField, areaMesh>> tfld =
            this->distributeField(fld);

        if (isWriteProc_.good())
        {
            if (isWriteProc_)
            {
                tfld().write();
            }
        }
        else if (writeHandler_ && writeHandler_->good())
        {
            auto oldHandler = fileOperation::fileHandler(writeHandler_);
            const label oldComm = UPstream::commWorld(fileHandler().comm());

            tfld().write();

            writeHandler_ = fileOperation::fileHandler(oldHandler);
            UPstream::commWorld(oldComm);
        }
    }
}


template<class Type>
void Foam::faMeshDistributor::redistributeAndWrite
(
    PtrList<GeometricField<Type, faePatchField, edgeMesh>>& flds
) const
{
    for (auto& fld : flds)
    {
        tmp<GeometricField<Type, faePatchField, edgeMesh>> tfld =
            this->distributeField(fld);

        if (isWriteProc_.good())
        {
            if (isWriteProc_)
            {
                tfld().write();
            }
        }
        else if (writeHandler_ && writeHandler_->good())
        {
            auto oldHandler = fileOperation::fileHandler(writeHandler_);
            const label oldComm = UPstream::commWorld(fileHandler().comm());

            tfld().write();

            writeHandler_ = fileOperation::fileHandler(oldHandler);
            UPstream::commWorld(oldComm);
        }
    }
}
#endif


// ************************************************************************* //
