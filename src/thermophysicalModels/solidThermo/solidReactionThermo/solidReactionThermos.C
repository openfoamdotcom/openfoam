/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2015 OpenFOAM Foundation
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

#include "solidReactionThermo/makeReactingSolidThermo.H"
#include "solidReactionThermo/solidReactionThermo.H"
#include "solidThermo/heSolidThermo.H"

#include "specie/specie.H"
#include "equationOfState/rhoConst/rhoConst.H"
#include "thermo/hConst/hConstThermo.H"
#include "thermo/hPower/hPowerThermo.H"
#include "transport/const/constIsoSolidTransport.H"
#include "transport/const/constAnIsoSolidTransport.H"
#include "transport/exponential/exponentialSolidTransport.H"

#include "mixtures/reactingMixture/reactingMixture.H"
#include "mixtures/multiComponentMixture/multiComponentMixture.H"

#include "thermo/sensibleEnthalpy/sensibleEnthalpy.H"
#include "thermo/thermo.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/* * * * * * * * * * * * * * * * * Enthalpy-based * * * * * * * * * * * * * */

makeReactingSolidThermo
(
    solidReactionThermo,
    heSolidThermo,
    reactingMixture,
    constIsoSolidTransport,
    sensibleEnthalpy,
    hConstThermo,
    rhoConst,
    specie
);


makeReactingSolidThermo
(
    solidReactionThermo,
    heSolidThermo,
    reactingMixture,
    constIsoSolidTransport,
    sensibleEnthalpy,
    hPowerThermo,
    rhoConst,
    specie
);


makeReactingSolidThermo
(
    solidThermo,
    heSolidThermo,
    multiComponentMixture,
    constIsoSolidTransport,
    sensibleEnthalpy,
    hConstThermo,
    rhoConst,
    specie
);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
