/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2018 OpenFOAM Foundation
    Copyright (C) 2020-2023 OpenCFD Ltd.
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

#ifndef makeParcelCloudFunctionObjects_H
#define makeParcelCloudFunctionObjects_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "submodels/CloudFunctionObjects/FaceInteraction/FaceInteraction.H"
#include "submodels/CloudFunctionObjects/FacePostProcessing/FacePostProcessing.H"
#include "submodels/CloudFunctionObjects/ParticleCollector/ParticleCollector.H"
#include "submodels/CloudFunctionObjects/ParticleErosion/ParticleErosion.H"
#include "submodels/CloudFunctionObjects/ParticleTracks/ParticleTracks.H"
#include "submodels/CloudFunctionObjects/ParticleTrap/ParticleTrap.H"
#include "submodels/CloudFunctionObjects/ParticleZoneInfo/ParticleZoneInfo.H"
#include "submodels/CloudFunctionObjects/ParticleHistogram/ParticleHistogram.H"
#include "submodels/CloudFunctionObjects/ParticlePostProcessing/ParticlePostProcessing.H"
#include "submodels/CloudFunctionObjects/PatchCollisionDensity/PatchCollisionDensity.H"
#include "submodels/CloudFunctionObjects/PatchInteractionFields/PatchInteractionFields.H"
#include "submodels/CloudFunctionObjects/RemoveParcels/RemoveParcels.H"
#include "submodels/CloudFunctionObjects/VoidFraction/VoidFraction.H"
#include "submodels/CloudFunctionObjects/KinematicReynoldsNumber/KinematicReynoldsNumber.H"
#include "submodels/CloudFunctionObjects/KinematicWeberNumber/KinematicWeberNumber.H"
#include "submodels/CloudFunctionObjects/ParticleDose/ParticleDose.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeParcelCloudFunctionObjects(CloudType)                              \
                                                                               \
    makeCloudFunctionObject(CloudType);                                        \
                                                                               \
    makeCloudFunctionObjectType(FaceInteraction, CloudType);                   \
    makeCloudFunctionObjectType(FacePostProcessing, CloudType);                \
    makeCloudFunctionObjectType(ParticleCollector, CloudType);                 \
    makeCloudFunctionObjectType(ParticleErosion, CloudType);                   \
    makeCloudFunctionObjectType(ParticleTracks, CloudType);                    \
    makeCloudFunctionObjectType(ParticleTrap, CloudType);                      \
    makeCloudFunctionObjectType(ParticleZoneInfo, CloudType);                  \
    makeCloudFunctionObjectType(ParticleHistogram, CloudType);                 \
    makeCloudFunctionObjectType(ParticlePostProcessing, CloudType);            \
    makeCloudFunctionObjectType(PatchCollisionDensity, CloudType);             \
    makeCloudFunctionObjectType(PatchInteractionFields, CloudType);            \
    makeCloudFunctionObjectType(RemoveParcels, CloudType);                     \
    makeCloudFunctionObjectType(VoidFraction, CloudType);                      \
    makeCloudFunctionObjectType(KinematicReynoldsNumber, CloudType);           \
    makeCloudFunctionObjectType(KinematicWeberNumber, CloudType);              \
    makeCloudFunctionObjectType(ParticleDose, CloudType);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
