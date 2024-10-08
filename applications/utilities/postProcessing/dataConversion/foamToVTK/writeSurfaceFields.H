/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2021 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM, distributed under GPL-3.0-or-later.

Description
    Write surface fields from volume mesh

\*---------------------------------------------------------------------------*/

#ifndef writeSurfaceFields_H
#define writeSurfaceFields_H

#include "readFields.H"
#include "meshes/primitiveMesh/primitivePatch/primitivePatch.H"
#include "vtk/output/foamVtkGenericPatchGeoFieldsWriter.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Writer type for face zones + fields
typedef
    vtk::GenericPatchGeoFieldsWriter<primitiveFacePatch>
    vtkWriterType_faceZone;

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
