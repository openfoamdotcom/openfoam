/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2018-2021 OpenCFD Ltd.
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

#include "clouds/derived/basicHeterogeneousReactingCloud/basicHeterogeneousReactingCloud.H"

#include "parcels/include/makeReactingParcelCloudFunctionObjects.H"

// Kinematic
#include "parcels/include/makeThermoParcelForces.H" // thermo variant
#include "parcels/include/makeParcelDispersionModels.H"
#include "parcels/include/makeReactingParcelInjectionModels.H" // Reacting variant
#include "parcels/include/makeParcelPatchInteractionModels.H"
#include "parcels/include/makeParcelStochasticCollisionModels.H"
#include "parcels/include/makeReactingParcelSurfaceFilmModels.H" // Reacting variant
#include "parcels/include/makeHeterogeneousReactingParcelHeterogeneousReactingModels.H"

// Thermodynamic
#include "parcels/include/makeParcelHeatTransferModels.H"

// Reacting
#include "parcels/include/makeReactingMultiphaseParcelCompositionModels.H"
#include "parcels/include/makeReactingParcelPhaseChangeModels.H"

// MPPIC sub-models
#include "parcels/include/makeMPPICParcelDampingModels.H"
#include "parcels/include/makeMPPICParcelIsotropyModels.H"
#include "parcels/include/makeMPPICParcelPackingModels.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeReactingParcelCloudFunctionObjects(basicHeterogeneousReactingCloud);

// Kinematic sub-models
makeThermoParcelForces(basicHeterogeneousReactingCloud);
makeParcelDispersionModels(basicHeterogeneousReactingCloud);
makeReactingParcelInjectionModels(basicHeterogeneousReactingCloud);
makeParcelPatchInteractionModels(basicHeterogeneousReactingCloud);
makeParcelStochasticCollisionModels(basicHeterogeneousReactingCloud);
makeReactingParcelSurfaceFilmModels(basicHeterogeneousReactingCloud);

// Thermo sub-models
makeParcelHeatTransferModels(basicHeterogeneousReactingCloud);

// Reacting sub-models
makeReactingMultiphaseParcelCompositionModels(basicHeterogeneousReactingCloud);
makeReactingParcelPhaseChangeModels(basicHeterogeneousReactingCloud);
makeHeterogeneousReactingParcelHeterogeneousReactingModels
(
    basicHeterogeneousReactingCloud
);

// MPPIC sub-models
makeMPPICParcelDampingModels(basicHeterogeneousReactingCloud);
makeMPPICParcelIsotropyModels(basicHeterogeneousReactingCloud);
makeMPPICParcelPackingModels(basicHeterogeneousReactingCloud);

// ************************************************************************* //
