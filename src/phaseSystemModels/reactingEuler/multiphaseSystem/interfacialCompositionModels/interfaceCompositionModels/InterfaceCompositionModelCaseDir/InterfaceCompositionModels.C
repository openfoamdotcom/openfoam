/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2015-2018 OpenFOAM Foundation
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

#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "interfaceCompositionModel/interfaceCompositionModel.H"
#include "interfacialCompositionModels/interfaceCompositionModels/InterfaceCompositionModelCaseDir/InterfaceCompositionModelPascal1.H"
#include "interfacialCompositionModels/interfaceCompositionModels/Henry/Henry.H"
#include "interfacialCompositionModels/interfaceCompositionModels/NonRandomTwoLiquid/NonRandomTwoLiquid.H"
#include "interfacialCompositionModels/interfaceCompositionModels/Raoult/Raoult.H"
#include "interfacialCompositionModels/interfaceCompositionModels/Saturated/Saturated.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "makeReactionThermo.H"

#include "include/thermoPhysicsTypes.H"

#include "equationOfState/rhoConst/rhoConst.H"
#include "equationOfState/perfectFluid/perfectFluid.H"

#include "mixtures/pureMixture/pureMixture.H"
#include "mixtures/multiComponentMixture/multiComponentMixture.H"
#include "mixtures/reactingMixture/reactingMixture.H"
#include "mixtures/SpecieMixture/SpecieMixture.H"

#include "rhoThermo/rhoThermo.H"
#include "rhoReactionThermo/rhoReactionThermo.H"
#include "rhoThermo/heRhoThermo.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeSpecieInterfaceCompositionModel(Model, Thermo1, Thermo2)           \
                                                                               \
    /* Composition at an interface with a multi-component mixture */           \
    makeSpecieInterfaceCompositionType                                         \
    (                                                                          \
        Model,                                                                 \
        heRhoThermo, rhoReactionThermo,                                        \
        multiComponentMixture, Thermo1,                                        \
        heRhoThermo, rhoReactionThermo,                                        \
        multiComponentMixture, Thermo2                                         \
    );                                                                         \
    makeSpecieInterfaceCompositionType                                         \
    (                                                                          \
        Model,                                                                 \
        heRhoThermo, rhoReactionThermo,                                        \
        reactingMixture, Thermo1,                                              \
        heRhoThermo, rhoReactionThermo,                                        \
        multiComponentMixture, Thermo2                                         \
    );                                                                         \
                                                                               \
    /* Composition at an interface with a reacting mixture */                  \
    makeSpecieInterfaceCompositionType                                         \
    (                                                                          \
        Model,                                                                 \
        heRhoThermo, rhoReactionThermo,                                        \
        multiComponentMixture, Thermo1,                                        \
        heRhoThermo, rhoReactionThermo,                                        \
        reactingMixture, Thermo2                                               \
    );                                                                         \
    makeSpecieInterfaceCompositionType                                         \
    (                                                                          \
        Model,                                                                 \
        heRhoThermo, rhoReactionThermo,                                        \
        reactingMixture, Thermo1,                                              \
        heRhoThermo, rhoReactionThermo,                                        \
        reactingMixture, Thermo2                                               \
    );

#define makeInterfaceCompositionModel(Model, Thermo1, Thermo2)                 \
                                                                               \
    /* Composition at an interface with a pure mixture */                      \
    makeInterfaceCompositionType                                               \
    (                                                                          \
        Model,                                                                 \
        heRhoThermo, rhoReactionThermo,                                        \
        multiComponentMixture, Thermo1,                                        \
        heRhoThermo, rhoThermo,                                                \
        pureMixture, Thermo2                                                   \
    );                                                                         \
    makeInterfaceCompositionType                                               \
    (                                                                          \
        Model,                                                                 \
        heRhoThermo, rhoReactionThermo,                                        \
        reactingMixture, Thermo1,                                              \
        heRhoThermo, rhoThermo,                                                \
        pureMixture, Thermo2                                                   \
    );                                                                         \
                                                                               \
    /* Composition at an interface with non-pure mixtures */                   \
    makeSpecieInterfaceCompositionModel(Model, Thermo1, Thermo2)

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    using namespace interfaceCompositionModels;

    // Gas-side models
    makeInterfaceCompositionModel
    (
        Saturated,
        constEThermoPhysics,
        constEThermoPhysics
    );
    makeInterfaceCompositionModel
    (
        Saturated,
        constGasEThermoPhysics,
        constEThermoPhysics
    );
    makeInterfaceCompositionModel
    (
        Saturated,
        gasEThermoPhysics,
        constEThermoPhysics
    );
    makeInterfaceCompositionModel
    (
        Saturated,
        constGasEThermoPhysics,
        constFluidEThermoPhysics
    );
    makeInterfaceCompositionModel
    (
        Saturated,
        gasEThermoPhysics,
        constFluidEThermoPhysics
    );

    makeSpecieInterfaceCompositionModel
    (
        NonRandomTwoLiquid,
        constEThermoPhysics,
        constEThermoPhysics
    );
    makeSpecieInterfaceCompositionModel
    (
        NonRandomTwoLiquid,
        constGasEThermoPhysics,
        constEThermoPhysics
    );
    makeSpecieInterfaceCompositionModel
    (
        NonRandomTwoLiquid,
        gasEThermoPhysics,
        constEThermoPhysics
    );
    makeSpecieInterfaceCompositionModel
    (
        NonRandomTwoLiquid,
        constGasEThermoPhysics,
        constFluidEThermoPhysics
    );
    makeSpecieInterfaceCompositionModel
    (
        NonRandomTwoLiquid,
        gasEThermoPhysics,
        constFluidEThermoPhysics
    );

    // Liquid-side models
    makeSpecieInterfaceCompositionModel
    (
        Henry,
        constEThermoPhysics,
        constEThermoPhysics
    );
    makeSpecieInterfaceCompositionModel
    (
        Henry,
        constEThermoPhysics,
        constGasEThermoPhysics
    );
    makeSpecieInterfaceCompositionModel
    (
        Henry,
        constEThermoPhysics,
        gasEThermoPhysics
    );
    makeSpecieInterfaceCompositionModel
    (
        Henry,
        constFluidEThermoPhysics,
        constGasEThermoPhysics
    );
    makeSpecieInterfaceCompositionModel
    (
        Henry,
        constFluidEThermoPhysics,
        gasEThermoPhysics
    );

    makeSpecieInterfaceCompositionModel
    (
        Raoult,
        constEThermoPhysics,
        constEThermoPhysics
    );
    makeSpecieInterfaceCompositionModel
    (
        Raoult,
        constEThermoPhysics,
        constGasEThermoPhysics
    );
    makeSpecieInterfaceCompositionModel
    (
        Raoult,
        constEThermoPhysics,
        gasEThermoPhysics
    );
    makeSpecieInterfaceCompositionModel
    (
        Raoult,
        constFluidEThermoPhysics,
        constGasEThermoPhysics
    );
    makeSpecieInterfaceCompositionModel
    (
        Raoult,
        constFluidEThermoPhysics,
        gasEThermoPhysics
    );
}

// ************************************************************************* //
