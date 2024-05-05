/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
    Copyright (C) 2020-2021 OpenCFD Ltd.
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
#include "mixtures/pureMixture/pureMixture.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/* * * * * * * * * * * * * * * Private Static Data * * * * * * * * * * * * * */

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureMixture,
    constTransport,
    sensibleEnthalpy,
    hConstThermo,
    perfectGas,
    specie
);

makeThermos
(
    rhoThermo,
    heRhoThermo,
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
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
    pureMixture,
    polynomialTransport,
    sensibleEnthalpy,
    hPolynomialThermo,
    incompressiblePerfectGas,
    specie
);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
