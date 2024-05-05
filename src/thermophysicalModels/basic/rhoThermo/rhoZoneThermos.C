/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2021,2022 OpenCFD Ltd.
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

#include "rhoThermo/rhoThermo.H"
#include "fluidThermo/makeThermo.H"

#include "specie/specie.H"
#include "equationOfState/perfectGas/perfectGas.H"
#include "equationOfState/incompressiblePerfectGas/incompressiblePerfectGas.H"
#include "equationOfState/Boussinesq/Boussinesq.H"
#include "equationOfState/rhoConst/rhoConst.H"
#include "equationOfState/rPolynomial/rPolynomial.H"
#include "equationOfState/perfectFluid/perfectFluid.H"
#include "equationOfState/PengRobinsonGas/PengRobinsonGas.H"
#include "equationOfState/adiabaticPerfectFluid/adiabaticPerfectFluid.H"
#include "equationOfState/icoTabulated/icoTabulated.H"

#include "thermo/hConst/hConstThermo.H"
#include "thermo/eConst/eConstThermo.H"
#include "thermo/janaf/janafThermo.H"
#include "thermo/hTabulated/hTabulatedThermo.H"
#include "thermo/sensibleEnthalpy/sensibleEnthalpy.H"
#include "thermo/sensibleInternalEnergy/sensibleInternalEnergy.H"
#include "thermo/thermo.H"

#include "transport/const/constTransport.H"
#include "transport/sutherland/sutherlandTransport.H"
#include "transport/WLF/WLFTransport.H"

#include "equationOfState/icoPolynomial/icoPolynomial.H"
#include "thermo/hPolynomial/hPolynomialThermo.H"
#include "transport/polynomial/polynomialTransport.H"
#include "transport/tabulated/tabulatedTransport.H"

#include "rhoThermo/heRhoThermo.H"
#include "mixtures/pureZoneMixture/pureZoneMixture.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/* * * * * * * * * * * * * * * Private Static Data * * * * * * * * * * * * * */

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleEnthalpy,
    hConstThermo,
    perfectGas,
    specie
);

// Note: pureZoneMixture copies mixture model for every evaluation of cell
//       so can become expensive for complex models (e.g. with tables)

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    sutherlandTransport,
    sensibleEnthalpy,
    hConstThermo,
    perfectGas,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    sutherlandTransport,
    sensibleEnthalpy,
    janafThermo,
    perfectGas,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    tabulatedTransport,
    sensibleEnthalpy,
    hTabulatedThermo,
    perfectGas,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleEnthalpy,
    hConstThermo,
    rhoConst,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleEnthalpy,
    hConstThermo,
    perfectFluid,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleEnthalpy,
    hConstThermo,
    rPolynomial,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    tabulatedTransport,
    sensibleEnthalpy,
    hTabulatedThermo,
    icoTabulated,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleEnthalpy,
    hConstThermo,
    icoTabulated,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleEnthalpy,
    hConstThermo,
    adiabaticPerfectFluid,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    polynomialTransport,
    sensibleEnthalpy,
    hPolynomialThermo,
    icoPolynomial,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    tabulatedTransport,
    sensibleEnthalpy,
    hPolynomialThermo,
    icoPolynomial,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    polynomialTransport,
    sensibleEnthalpy,
    hPolynomialThermo,
    rPolynomial,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleEnthalpy,
    hConstThermo,
    incompressiblePerfectGas,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    sutherlandTransport,
    sensibleEnthalpy,
    hConstThermo,
    incompressiblePerfectGas,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    sutherlandTransport,
    sensibleEnthalpy,
    hConstThermo,
    icoTabulated,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    sutherlandTransport,
    sensibleEnthalpy,
    janafThermo,
    incompressiblePerfectGas,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    sutherlandTransport,
    sensibleEnthalpy,
    janafThermo,
    icoTabulated,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    tabulatedTransport,
    sensibleEnthalpy,
    janafThermo,
    icoTabulated,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleEnthalpy,
    hConstThermo,
    Boussinesq,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    sutherlandTransport,
    sensibleEnthalpy,
    hConstThermo,
    Boussinesq,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    sutherlandTransport,
    sensibleEnthalpy,
    janafThermo,
    Boussinesq,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    sutherlandTransport,
    sensibleEnthalpy,
    hConstThermo,
    PengRobinsonGas,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    polynomialTransport,
    sensibleEnthalpy,
    hPolynomialThermo,
    PengRobinsonGas,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    polynomialTransport,
    sensibleEnthalpy,
    hPolynomialThermo,
    icoTabulated,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    polynomialTransport,
    sensibleEnthalpy,
    janafThermo,
    PengRobinsonGas,
    specie
);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleInternalEnergy,
    hConstThermo,
    perfectGas,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    tabulatedTransport,
    sensibleInternalEnergy,
    hTabulatedThermo,
    icoTabulated,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    sutherlandTransport,
    sensibleInternalEnergy,
    hConstThermo,
    perfectGas,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    sutherlandTransport,
    sensibleInternalEnergy,
    hConstThermo,
    icoTabulated,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    sutherlandTransport,
    sensibleInternalEnergy,
    janafThermo,
    perfectGas,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    sutherlandTransport,
    sensibleInternalEnergy,
    janafThermo,
    icoTabulated,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleInternalEnergy,
    hConstThermo,
    rhoConst,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleInternalEnergy,
    eConstThermo,
    rhoConst,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleInternalEnergy,
    hConstThermo,
    perfectFluid,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleInternalEnergy,
    hConstThermo,
    rPolynomial,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleInternalEnergy,
    eConstThermo,
    perfectFluid,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleInternalEnergy,
    eConstThermo,
    perfectGas,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleInternalEnergy,
    eConstThermo,
    rPolynomial,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleInternalEnergy,
    hConstThermo,
    adiabaticPerfectFluid,
    specie
);


makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleInternalEnergy,
    eConstThermo,
    adiabaticPerfectFluid,
    specie
);


makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    polynomialTransport,
    sensibleInternalEnergy,
    hPolynomialThermo,
    icoPolynomial,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    tabulatedTransport,
    sensibleInternalEnergy,
    hPolynomialThermo,
    icoPolynomial,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    polynomialTransport,
    sensibleInternalEnergy,
    hPolynomialThermo,
    icoTabulated,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleInternalEnergy,
    hConstThermo,
    incompressiblePerfectGas,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    sutherlandTransport,
    sensibleInternalEnergy,
    hConstThermo,
    incompressiblePerfectGas,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    sutherlandTransport,
    sensibleInternalEnergy,
    janafThermo,
    incompressiblePerfectGas,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    constTransport,
    sensibleInternalEnergy,
    hConstThermo,
    Boussinesq,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    sutherlandTransport,
    sensibleInternalEnergy,
    hConstThermo,
    Boussinesq,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    sutherlandTransport,
    sensibleInternalEnergy,
    janafThermo,
    Boussinesq,
    specie
);


makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    WLFTransport,
    sensibleInternalEnergy,
    eConstThermo,
    rhoConst,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    polynomialTransport,
    sensibleEnthalpy,
    hPolynomialThermo,
    perfectGas,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureZoneMixture,
    polynomialTransport,
    sensibleEnthalpy,
    hPolynomialThermo,
    incompressiblePerfectGas,
    specie
);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
