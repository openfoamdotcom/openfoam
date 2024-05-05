/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
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

#include "psiuReactionThermo/psiuReactionThermo.H"
#include "psiuReactionThermo/heheuPsiThermo.H"

#include "makeReactionThermo.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"

#include "specie/specie.H"
#include "equationOfState/perfectGas/perfectGas.H"
#include "thermo/hConst/hConstThermo.H"
#include "thermo/janaf/janafThermo.H"
#include "thermo/thermo/thermo.H"
#include "transport/const/constTransport.H"
#include "transport/sutherland/sutherlandTransport.H"

#include "thermo/absoluteEnthalpy/absoluteEnthalpy.H"
#include "thermo/absoluteInternalEnergy/absoluteInternalEnergy.H"

#include "mixtures/homogeneousMixture/homogeneousMixture.H"
#include "mixtures/inhomogeneousMixture/inhomogeneousMixture.H"
#include "mixtures/veryInhomogeneousMixture/veryInhomogeneousMixture.H"
#include "mixtures/multiComponentMixture/multiComponentMixture.H"
#include "mixtures/egrMixture/egrMixture.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * h-hu-Thermos * * * * * * * * * * * * * * * //

makeReactionThermos
(
    psiThermo,
    psiuReactionThermo,
    heheuPsiThermo,
    homogeneousMixture,
    constTransport,
    absoluteEnthalpy,
    hConstThermo,
    perfectGas,
    specie
);

makeReactionThermos
(
    psiThermo,
    psiuReactionThermo,
    heheuPsiThermo,
    inhomogeneousMixture,
    constTransport,
    absoluteEnthalpy,
    hConstThermo,
    perfectGas,
    specie
);

makeReactionThermos
(
    psiThermo,
    psiuReactionThermo,
    heheuPsiThermo,
    veryInhomogeneousMixture,
    constTransport,
    absoluteEnthalpy,
    hConstThermo,
    perfectGas,
    specie
);

makeReactionThermos
(
    psiThermo,
    psiuReactionThermo,
    heheuPsiThermo,
    egrMixture,
    constTransport,
    absoluteEnthalpy,
    hConstThermo,
    perfectGas,
    specie
);


makeReactionThermos
(
    psiThermo,
    psiuReactionThermo,
    heheuPsiThermo,
    homogeneousMixture,
    constTransport,
    absoluteEnthalpy,
    janafThermo,
    perfectGas,
    specie
);

makeReactionThermos
(
    psiThermo,
    psiuReactionThermo,
    heheuPsiThermo,
    homogeneousMixture,
    sutherlandTransport,
    absoluteEnthalpy,
    janafThermo,
    perfectGas,
    specie
);

makeReactionThermos
(
    psiThermo,
    psiuReactionThermo,
    heheuPsiThermo,
    inhomogeneousMixture,
    sutherlandTransport,
    absoluteEnthalpy,
    janafThermo,
    perfectGas,
    specie
);

makeReactionThermos
(
    psiThermo,
    psiuReactionThermo,
    heheuPsiThermo,
    veryInhomogeneousMixture,
    sutherlandTransport,
    absoluteEnthalpy,
    janafThermo,
    perfectGas,
    specie
);

makeReactionThermos
(
    psiThermo,
    psiuReactionThermo,
    heheuPsiThermo,
    egrMixture,
    sutherlandTransport,
    absoluteEnthalpy,
    janafThermo,
    perfectGas,
    specie
);


makeReactionThermos
(
    psiThermo,
    psiuReactionThermo,
    heheuPsiThermo,
    homogeneousMixture,
    sutherlandTransport,
    absoluteInternalEnergy,
    janafThermo,
    perfectGas,
    specie
);

makeReactionThermos
(
    psiThermo,
    psiuReactionThermo,
    heheuPsiThermo,
    inhomogeneousMixture,
    sutherlandTransport,
    absoluteInternalEnergy,
    janafThermo,
    perfectGas,
    specie
);

makeReactionThermos
(
    psiThermo,
    psiuReactionThermo,
    heheuPsiThermo,
    veryInhomogeneousMixture,
    sutherlandTransport,
    absoluteInternalEnergy,
    janafThermo,
    perfectGas,
    specie
);

makeReactionThermos
(
    psiThermo,
    psiuReactionThermo,
    heheuPsiThermo,
    egrMixture,
    sutherlandTransport,
    absoluteInternalEnergy,
    janafThermo,
    perfectGas,
    specie
);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
