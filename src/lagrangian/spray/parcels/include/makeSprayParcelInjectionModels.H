/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2016 OpenCFD Ltd.
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

#ifndef makeSprayParcelInjectionModels_H
#define makeSprayParcelInjectionModels_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "submodels/Kinematic/InjectionModel/CellZoneInjection/CellZoneInjection.H"
#include "submodels/Kinematic/InjectionModel/ConeInjection/ConeInjection.H"
#include "submodels/Kinematic/InjectionModel/ConeNozzleInjection/ConeNozzleInjection.H"
#include "submodels/Kinematic/InjectionModel/FieldActivatedInjection/FieldActivatedInjection.H"
#include "submodels/Kinematic/InjectionModel/InjectedParticleDistributionInjection/InjectedParticleDistributionInjection.H"
#include "submodels/Kinematic/InjectionModel/InjectedParticleInjection/InjectedParticleInjection.H"
#include "submodels/Kinematic/InjectionModel/InflationInjection/InflationInjection.H"
#include "submodels/Kinematic/InjectionModel/ManualInjection/ManualInjection.H"
#include "submodels/Kinematic/InjectionModel/NoInjection/NoInjection.H"
#include "submodels/Kinematic/InjectionModel/PatchInjection/PatchInjectionPascal.H"
#include "submodels/Kinematic/InjectionModel/PatchFlowRateInjection/PatchFlowRateInjection.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeSprayParcelInjectionModels(CloudType)                              \
                                                                               \
    makeInjectionModel(CloudType);                                             \
                                                                               \
    makeInjectionModelType(CellZoneInjection, CloudType);                      \
    makeInjectionModelType(ConeInjection, CloudType);                          \
    makeInjectionModelType(ConeNozzleInjection, CloudType);                    \
    makeInjectionModelType(FieldActivatedInjection, CloudType);                \
    makeInjectionModelType(InjectedParticleDistributionInjection, CloudType);  \
    makeInjectionModelType(InjectedParticleInjection, CloudType);              \
    makeInjectionModelType(InflationInjection, CloudType);                     \
    makeInjectionModelType(ManualInjection, CloudType);                        \
    makeInjectionModelType(NoInjection, CloudType);                            \
    makeInjectionModelType(PatchFlowRateInjection, CloudType);                 \
    makeInjectionModelType(PatchInjection, CloudType);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
