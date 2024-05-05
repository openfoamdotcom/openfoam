/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2013-2016 OpenFOAM Foundation
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

#include "turbulentFluidThermoModels/turbulentFluidThermoModels.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

defineTurbulenceModelTypes
(
    geometricOneField,
    volScalarField,
    compressibleTurbulenceModel,
    CompressibleTurbulenceModel,
    ThermalDiffusivity,
    fluidThermo
);

makeBaseTurbulenceModel
(
    geometricOneField,
    volScalarField,
    compressibleTurbulenceModel,
    CompressibleTurbulenceModel,
    ThermalDiffusivity,
    fluidThermo
);


// -------------------------------------------------------------------------- //
// Laminar models
// -------------------------------------------------------------------------- //

#include "laminar/Stokes/Stokes.H"
makeLaminarModel(Stokes);

#include "laminar/generalizedNewtonian/generalizedNewtonian.H"
makeLaminarModel(generalizedNewtonian);

#include "laminar/Maxwell/Maxwell.H"
makeLaminarModel(Maxwell);


// -------------------------------------------------------------------------- //
// RAS models
// -------------------------------------------------------------------------- //

#include "RAS/SpalartAllmaras/SpalartAllmaras.H"
makeRASModel(SpalartAllmaras);

#include "RAS/kEpsilon/kEpsilon.H"
makeRASModel(kEpsilon);

#include "RAS/RNGkEpsilon/RNGkEpsilon.H"
makeRASModel(RNGkEpsilon);

#include "RAS/realizableKE/realizableKE.H"
makeRASModel(realizableKE);

#include "RAS/buoyantKEpsilon/buoyantKEpsilon.H"
makeRASModel(buoyantKEpsilon);

#include "RAS/LaunderSharmaKE/LaunderSharmaKE.H"
makeRASModel(LaunderSharmaKE);

#include "RAS/kEpsilonPhitF/kEpsilonPhitF.H"
makeRASModel(kEpsilonPhitF);

#include "RAS/kOmega/kOmega.H"
makeRASModel(kOmega);

#include "RAS/kOmegaSST/kOmegaSST.H"
makeRASModel(kOmegaSST);

#include "RAS/kOmegaSSTSAS/kOmegaSSTSAS.H"
makeRASModel(kOmegaSSTSAS);

#include "RAS/kOmegaSSTLM/kOmegaSSTLM.H"
makeRASModel(kOmegaSSTLM);

#include "RAS/LRR/LRR.H"
makeRASModel(LRR);

#include "RAS/SSG/SSG.H"
makeRASModel(SSG);

#include "RAS/EBRSM/EBRSM.H"
makeRASModel(EBRSM);


// -------------------------------------------------------------------------- //
// LES models
// -------------------------------------------------------------------------- //

#include "LES/Smagorinsky/Smagorinsky.H"
makeLESModel(Smagorinsky);

#include "LES/WALE/WALE.H"
makeLESModel(WALE);

#include "LES/kEqn/kEqn.H"
makeLESModel(kEqn);

#include "LES/dynamicKEqn/dynamicKEqn.H"
makeLESModel(dynamicKEqn);

#include "LES/dynamicLagrangian/dynamicLagrangian.H"
makeLESModel(dynamicLagrangian);

#include "LES/sigma/sigma.H"
makeLESModel(sigma);

#include "DES/SpalartAllmarasDES/SpalartAllmarasDES.H"
makeLESModel(SpalartAllmarasDES);

#include "DES/SpalartAllmarasDDES/SpalartAllmarasDDES.H"
makeLESModel(SpalartAllmarasDDES);

#include "DES/SpalartAllmarasIDDES/SpalartAllmarasIDDES.H"
makeLESModel(SpalartAllmarasIDDES);

#include "LES/DeardorffDiffStress/DeardorffDiffStress.H"
makeLESModel(DeardorffDiffStress);

#include "DES/kOmegaSSTDES/kOmegaSSTDES.H"
makeLESModel(kOmegaSSTDES);

#include "DES/kOmegaSSTDDES/kOmegaSSTDDES.H"
makeLESModel(kOmegaSSTDDES);

#include "DES/kOmegaSSTIDDES/kOmegaSSTIDDES.H"
makeLESModel(kOmegaSSTIDDES);


// ************************************************************************* //
