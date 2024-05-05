/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2014-2018 OpenFOAM Foundation
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

#include "turbulence/phaseCompressibleTurbulenceModel.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"
#include "turbulentFluidThermoModels/compressible_makeTurbulenceModel.H"

#include "laminar/laminarModel/laminarModel.H"
#include "RAS/RASModel/RASModel.H"
#include "LES/LESModel/LESModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Base models defined in multiphaseCompressibleTurbulenceModels.C
//
// Additional two-phase only models

// Typedefs
defineTurbulenceModelTypes
(
    volScalarField,
    volScalarField,
    compressibleTurbulenceModel,
    PhaseCompressibleTurbulenceModel,
    ThermalDiffusivity,
    phaseModel
);

#define makeRASModel(Type)                                                     \
    makeTemplatedTurbulenceModel                                               \
    (phaseModelPhaseCompressibleTurbulenceModel, RAS, Type)

#define makeLESModel(Type)                                                     \
    makeTemplatedTurbulenceModel                                               \
    (phaseModelPhaseCompressibleTurbulenceModel, LES, Type)


// -------------------------------------------------------------------------- //
// Laminar models
// -------------------------------------------------------------------------- //

// "Stokes.H"


// -------------------------------------------------------------------------- //
// RAS models
// -------------------------------------------------------------------------- //

// "kEpsilon.H"
// "kOmegaSST.H"

#include "TurbulenceModels/phaseCompressible/RAS/kOmegaSSTSato/kOmegaSSTSato.H"
makeRASModel(kOmegaSSTSato);

#include "TurbulenceModels/phaseCompressible/RAS/mixtureKEpsilon/mixtureKEpsilon.H"
makeRASModel(mixtureKEpsilon);

#include "TurbulenceModels/phaseCompressible/RAS/LaheyKEpsilon/LaheyKEpsilon.H"
makeRASModel(LaheyKEpsilon);

#include "TurbulenceModels/phaseCompressible/RAS/continuousGasKEpsilon/continuousGasKEpsilon.H"
makeRASModel(continuousGasKEpsilon);


// -------------------------------------------------------------------------- //
// LES models
// -------------------------------------------------------------------------- //

// "Smagorinsky.H"
// "kEqn.H"

#include "TurbulenceModels/phaseCompressible/LES/SmagorinskyZhang/SmagorinskyZhang.H"
makeLESModel(SmagorinskyZhang);

#include "TurbulenceModels/phaseCompressible/LES/Niceno/NicenoKEqn.H"
makeLESModel(NicenoKEqn);

#include "TurbulenceModels/phaseCompressible/LES/continuousGasKEqn/continuousGasKEqn.H"
makeLESModel(continuousGasKEqn);


// -------------------------------------------------------------------------- //
// Additional models
// -------------------------------------------------------------------------- //

#include "kineticTheoryModels/kineticTheoryModel/kineticTheoryModel.H"
makeTurbulenceModel
(phaseModelPhaseCompressibleTurbulenceModel, RAS, kineticTheoryModel);

#include "phasePressureModel/phasePressureModel.H"
makeTurbulenceModel
(phaseModelPhaseCompressibleTurbulenceModel, RAS, phasePressureModel);


// ************************************************************************* //
