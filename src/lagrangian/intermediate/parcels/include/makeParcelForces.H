/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2023 OpenCFD Ltd.
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

#ifndef makeParcelForces_H
#define makeParcelForces_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "submodels/Kinematic/ParticleForces/Drag/SphereDrag/SphereDragForce.H"
#include "submodels/Kinematic/ParticleForces/Drag/NonSphereDrag/NonSphereDragForce.H"
#include "submodels/Kinematic/ParticleForces/Drag/WenYuDrag/WenYuDragForce.H"
#include "submodels/Kinematic/ParticleForces/Drag/ErgunWenYuDrag/ErgunWenYuDragForce.H"
#include "submodels/Kinematic/ParticleForces/Drag/PlessisMasliyahDrag/PlessisMasliyahDragForce.H"

#include "submodels/Kinematic/ParticleForces/Lift/SaffmanMeiLift/SaffmanMeiLiftForce.H"
#include "submodels/Kinematic/ParticleForces/Lift/TomiyamaLift/TomiyamaLiftForce.H"

#include "submodels/Kinematic/ParticleForces/Gravity/GravityForce.H"
#include "submodels/Kinematic/ParticleForces/NonInertialFrame/NonInertialFrameForce.H"
#include "submodels/Kinematic/ParticleForces/Paramagnetic/ParamagneticForce.H"
#include "submodels/Kinematic/ParticleForces/PressureGradient/PressureGradientForce.H"
#include "submodels/Kinematic/ParticleForces/SRF/SRFForce.H"
#include "submodels/Kinematic/ParticleForces/VirtualMass/VirtualMassForce.H"
#include "submodels/Kinematic/ParticleForces/Interface/InterfaceForce.H"
#include "submodels/Kinematic/ParticleForces/Coulomb/CoulombForce.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeParcelForces(CloudType)                                            \
                                                                               \
    makeParticleForceModel(CloudType);                                         \
    makeParticleForceModelType(SphereDragForce, CloudType);                    \
    makeParticleForceModelType(NonSphereDragForce, CloudType);                 \
    makeParticleForceModelType(WenYuDragForce, CloudType);                     \
    makeParticleForceModelType(ErgunWenYuDragForce, CloudType);                \
    makeParticleForceModelType(PlessisMasliyahDragForce, CloudType);           \
    makeParticleForceModelType(SaffmanMeiLiftForce, CloudType);                \
    makeParticleForceModelType(TomiyamaLiftForce, CloudType);                  \
    makeParticleForceModelType(GravityForce, CloudType);                       \
    makeParticleForceModelType(NonInertialFrameForce, CloudType);              \
    makeParticleForceModelType(ParamagneticForce, CloudType);                  \
    makeParticleForceModelType(PressureGradientForce, CloudType);              \
    makeParticleForceModelType(SRFForce, CloudType);                           \
    makeParticleForceModelType(VirtualMassForce, CloudType);                   \
    makeParticleForceModelType(InterfaceForce, CloudType);                     \
    makeParticleForceModelType(CoulombForce, CloudType);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
