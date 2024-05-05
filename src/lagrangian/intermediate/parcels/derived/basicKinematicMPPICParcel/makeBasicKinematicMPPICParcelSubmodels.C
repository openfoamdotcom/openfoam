/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2013-2015 OpenFOAM Foundation
    Copyright (C) 2020 OpenCFD Ltd.
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

#include "clouds/derived/basicKinematicMPPICCloud/basicKinematicMPPICCloud.H"

#include "parcels/include/makeParcelCloudFunctionObjects.H"

// Kinematic sub-models
#include "parcels/include/makeParcelForces.H"
#include "parcels/include/makeParcelDispersionModels.H"
#include "parcels/include/makeParcelInjectionModels.H"
#include "parcels/include/makeParcelPatchInteractionModels.H"
#include "parcels/include/makeParcelStochasticCollisionModels.H"
#include "parcels/include/makeParcelSurfaceFilmModels.H"

// MPPIC sub-models
#include "parcels/include/makeMPPICParcelDampingModels.H"
#include "parcels/include/makeMPPICParcelIsotropyModels.H"
#include "parcels/include/makeMPPICParcelPackingModels.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeParcelCloudFunctionObjects(basicKinematicMPPICCloud);

// Kinematic sub-models
makeParcelForces(basicKinematicMPPICCloud);

makeParcelDispersionModels(basicKinematicMPPICCloud);
makeParcelInjectionModels(basicKinematicMPPICCloud);
makeParcelPatchInteractionModels(basicKinematicMPPICCloud);
makeParcelStochasticCollisionModels(basicKinematicMPPICCloud);
makeParcelSurfaceFilmModels(basicKinematicMPPICCloud);

// MPPIC sub-models
// WIP: These models are defined in Kinematic and MPPIC clouds temporarily
makeMPPICParcelDampingModels(basicKinematicMPPICCloud);
makeMPPICCloudParcelDampingModels(basicKinematicMPPICCloud);

makeMPPICParcelIsotropyModels(basicKinematicMPPICCloud);
makeMPPICCloudParcelIsotropyModels(basicKinematicMPPICCloud);

makeMPPICParcelPackingModels(basicKinematicMPPICCloud);
makeMPPICCloudParcelPackingModels(basicKinematicMPPICCloud);


// ************************************************************************* //
