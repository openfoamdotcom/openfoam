/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2015 OpenFOAM Foundation
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

#include "clouds/derived/basicKinematicCloud/basicKinematicCloud.H"

#include "parcels/include/makeParcelCloudFunctionObjects.H"

// Kinematic
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

makeParcelCloudFunctionObjects(basicKinematicCloud);

// Kinematic sub-models
makeParcelForces(basicKinematicCloud);
makeParcelDispersionModels(basicKinematicCloud);
makeParcelInjectionModels(basicKinematicCloud);
makeParcelPatchInteractionModels(basicKinematicCloud);
makeParcelStochasticCollisionModels(basicKinematicCloud);
makeParcelSurfaceFilmModels(basicKinematicCloud);

// MPPIC sub-models
makeMPPICParcelDampingModels(basicKinematicCloud);
makeMPPICParcelIsotropyModels(basicKinematicCloud);
makeMPPICParcelPackingModels(basicKinematicCloud);


// ************************************************************************* //
