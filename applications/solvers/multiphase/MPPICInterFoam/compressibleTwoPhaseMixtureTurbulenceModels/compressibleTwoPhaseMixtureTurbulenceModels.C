/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
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

#include "PhaseCompressibleTurbulenceModel.H"
#include "immiscibleIncompressibleTwoPhaseMixture.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"
#include "makeTurbulenceModel.H"

#include "turbulentTransportModels/turbulentTransportModel.H"
#include "LES/LESModel/LESModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

defineTurbulenceModelTypes
(
    volScalarField,
    geometricOneField,
    incompressibleTurbulenceModel,
    PhaseCompressibleTurbulenceModel,
    immiscibleIncompressibleTwoPhaseMixture
);

makeBaseTurbulenceModel
(
    volScalarField,
    volScalarField,
    compressibleTurbulenceModel,
    PhaseCompressibleTurbulenceModel,
    immiscibleIncompressibleTwoPhaseMixture
);

#define makeLaminarModel(Type)                                                 \
    makeTemplatedTurbulenceModel                                               \
    (                                                                          \
       immiscibleIncompressibleTwoPhaseMixturePhaseCompressibleTurbulenceModel,\
        laminar,                                                               \
        Type                                                                   \
    )

#define makeRASModel(Type)                                                     \
    makeTemplatedTurbulenceModel                                               \
    (                                                                          \
       immiscibleIncompressibleTwoPhaseMixturePhaseCompressibleTurbulenceModel,\
        RAS,                                                                   \
        Type                                                                   \
    )

#define makeLESModel(Type)                                                     \
    makeTemplatedTurbulenceModel                                               \
    (                                                                          \
       immiscibleIncompressibleTwoPhaseMixturePhaseCompressibleTurbulenceModel,\
        LES,                                                                   \
        Type                                                                   \
    )

#include "laminar/Stokes/Stokes.H"
makeLaminarModel(Stokes);

#include "turbulenceModels/turbulenceModelVariables/RAS/kEpsilon/kEpsilon.H"
makeRASModel(kEpsilon);

#include "LES/Smagorinsky/Smagorinsky.H"
makeLESModel(Smagorinsky);

#include "LES/kEqn/kEqn.H"
makeLESModel(kEqn);

#include "RAS/kOmega/kOmega.H"
makeRASModel(kOmega);


// ************************************************************************* //
