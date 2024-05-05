/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2015 OpenFOAM Foundation
    Copyright (C) 2022 OpenCFD Ltd
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

#include "solidThermo/makeSolidThermo.H"
#include "solidThermo/solidThermo.H"
#include "solidThermo/heSolidThermo.H"

#include "specie/specie.H"
#include "equationOfState/rhoConst/rhoConst.H"
#include "equationOfState/icoPolynomial/icoPolynomial.H"
#include "equationOfState/icoTabulated/icoTabulated.H"
#include "thermo/hConst/hConstThermo.H"
#include "thermo/hPower/hPowerThermo.H"
#include "thermo/hPolynomial/hPolynomialThermo.H"
#include "thermo/hTabulated/hTabulatedThermo.H"
#include "transport/const/constIsoSolidTransport.H"
#include "transport/const/constAnIsoSolidTransport.H"
#include "transport/exponential/exponentialSolidTransport.H"
#include "transport/polynomial/polynomialSolidTransport.H"
#include "transport/tabulated/tabulatedSolidTransport.H"
#include "transport/tabulated/tabulatedAnIsoSolidTransport.H"
#include "mixtures/pureMixture/pureMixture.H"
#include "thermo/sensibleEnthalpy/sensibleEnthalpy.H"
#include "thermo/sensibleInternalEnergy/sensibleInternalEnergy.H"
#include "thermo/thermo/thermo.H"

#include "include/solidThermoPhysicsTypes.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/* * * * * * * * * * * * * * * * * Enthalpy-based * * * * * * * * * * * * * */

makeSolidThermo
(
    solidThermo,
    heSolidThermo,
    pureMixture,
    constIsoSolidTransport,
    sensibleEnthalpy,
    hConstThermo,
    rhoConst,
    specie
);

makeSolidThermo
(
    solidThermo,
    heSolidThermo,
    pureMixture,
    constAnIsoSolidTransport,
    sensibleEnthalpy,
    hConstThermo,
    rhoConst,
    specie
);

makeSolidThermo
(
    solidThermo,
    heSolidThermo,
    pureMixture,
    exponentialSolidTransport,
    sensibleEnthalpy,
    hPowerThermo,
    rhoConst,
    specie
);

makeSolidThermo
(
    solidThermo,
    heSolidThermo,
    pureMixture,
    polynomialSolidTransport,
    sensibleEnthalpy,
    hPolynomialThermo,
    icoPolynomial,
    specie
);

makeSolidThermo
(
    solidThermo,
    heSolidThermo,
    pureMixture,
    tabulatedSolidTransport,
    sensibleEnthalpy,
    hTabulatedThermo,
    icoPolynomial,
    specie
);

makeSolidThermo
(
    solidThermo,
    heSolidThermo,
    pureMixture,
    tabulatedSolidTransport,
    sensibleEnthalpy,
    hTabulatedThermo,
    icoTabulated,
    specie
);

makeSolidThermo
(
    solidThermo,
    heSolidThermo,
    pureMixture,
    tabulatedAnIsoSolidTransport,
    sensibleEnthalpy,
    hTabulatedThermo,
    icoPolynomial,
    specie
);

makeSolidThermoPhysicsType
(
    solidThermo,
    heSolidThermo,
    pureMixture,
    hTransportThermoPoly8SolidThermoPhysics
);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
