/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2017-2022 OpenCFD Ltd
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

#include "CompressibleTurbulenceModel/CompressibleTurbulenceModelPascal.H"
#include "compressibleTurbulenceModel.H"
#include "multiphaseSystem/multiphaseSystem.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"
#include "turbulentFluidThermoModels/compressible_makeTurbulenceModel.H"

#include "ThermalDiffusivity/ThermalDiffusivity.H"

#include "laminar/laminarModel/laminarModel.H"
#include "RAS/RASModel/RASModel.H"
#include "LES/LESModel/LESModel.H"

using namespace Foam::multiphaseInter;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

defineTurbulenceModelTypes
(
    geometricOneField,
    volScalarField,
    compressibleTurbulenceModel,
    CompressibleTurbulenceModel,
    ThermalDiffusivity,
    multiphaseSystem
);

makeBaseTurbulenceModel
(
    geometricOneField,
    volScalarField,
    compressibleTurbulenceModel,
    CompressibleTurbulenceModel,
    ThermalDiffusivity,
    multiphaseSystem
);

#define makeLaminarModel(Type)                                                 \
    makeTemplatedLaminarModel                                                  \
    (multiphaseSystemCompressibleTurbulenceModel, laminar, Type)

#define makeRASModel(Type)                                                     \
    makeTemplatedTurbulenceModel                                               \
    (multiphaseSystemCompressibleTurbulenceModel, RAS, Type)

#define makeLESModel(Type)                                                     \
    makeTemplatedTurbulenceModel                                               \
    (multiphaseSystemCompressibleTurbulenceModel, LES, Type)


// -------------------------------------------------------------------------- //
// Laminar models
// -------------------------------------------------------------------------- //

#include "laminar/Stokes/Stokes.H"
makeLaminarModel(Stokes);

#include "laminar/generalizedNewtonian/generalizedNewtonian.H"
makeLaminarModel(generalizedNewtonian);

// -------------------------------------------------------------------------- //
// RAS models
// -------------------------------------------------------------------------- //

#include "turbulenceModels/turbulenceModelVariables/RAS/kEpsilon/kEpsilon.H"
makeRASModel(kEpsilon);


// -------------------------------------------------------------------------- //
// LES models
// -------------------------------------------------------------------------- //

#include "LES/Smagorinsky/Smagorinsky.H"
makeLESModel(Smagorinsky);

#include "LES/kEqn/kEqn.H"
makeLESModel(kEqn);


// ************************************************************************* //
