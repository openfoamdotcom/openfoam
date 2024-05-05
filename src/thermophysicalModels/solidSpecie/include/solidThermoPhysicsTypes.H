/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2015 OpenFOAM Foundation
    Copyright (C) 2022 OpenCFD Ltd.
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

Typedefs
    Foam::solidThermoPhysicsTypes

Description
    Type definitions for solid-thermo-physics models

\*---------------------------------------------------------------------------*/

#ifndef solidThermoPhysicsTypes_H
#define solidThermoPhysicsTypes_H

#include "specie/specie.H"
#include "equationOfState/rhoConst/rhoConst.H"
#include "equationOfState/icoPolynomial/icoPolynomial.H"
#include "equationOfState/icoTabulated/icoTabulated.H"
#include "thermo/hConst/hConstThermo.H"
#include "thermo/hPolynomial/hPolynomialThermo.H"
#include "thermo/hPower/hPowerThermo.H"
#include "thermo/hTabulated/hTabulatedThermo.H"
#include "transport/const/constIsoSolidTransport.H"
#include "transport/const/constAnIsoSolidTransport.H"
#include "transport/exponential/exponentialSolidTransport.H"
#include "transport/polynomial/polynomialSolidTransport.H"
#include "transport/tabulated/tabulatedSolidTransport.H"

#include "thermo/sensibleEnthalpy/sensibleEnthalpy.H"
#include "thermo/thermo.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    typedef
        constIsoSolidTransport
        <
            species::thermo
            <
                hConstThermo
                <
                    rhoConst<specie>
                >,
                sensibleEnthalpy
            >
        > hConstSolidThermoPhysics;

    typedef
        exponentialSolidTransport
        <
            species::thermo
            <
                hPowerThermo
                <
                    rhoConst<specie>
                >,
                sensibleEnthalpy
            >
        > hPowerSolidThermoPhysics;

    typedef
        polynomialSolidTransport
        <
            species::thermo
            <
                hPolynomialThermo
                <
                    rhoConst<specie>,
                    8
                >,
                sensibleEnthalpy
            >,
            8
        > hTransportThermoPoly8SolidThermoPhysics;

     typedef
        constIsoSolidTransport
        <
            species::thermo
            <
                hPowerThermo
                <
                    rhoConst<specie>
                >,
                sensibleEnthalpy
            >
        > hExpKappaConstSolidThermoPhysics;

    typedef
        polynomialSolidTransport
        <
            species::thermo
            <
                hPolynomialThermo
                <
                    icoPolynomial<specie, 8>,
                    8
                >,
                sensibleEnthalpy
            >,
            8
        > hPolyTranspPolyIcoSolidThermoPhysics;

     typedef
        tabulatedSolidTransport
        <
            species::thermo
            <
                hTabulatedThermo
                <
                    icoPolynomial<specie, 8>
                >,
                sensibleEnthalpy
            >
        > hTabulatedPolyIcoSolidThermoPhysics;

    typedef
        tabulatedSolidTransport
        <
            species::thermo
            <
                hTabulatedThermo
                <
                    icoTabulated<specie>
                >,
                sensibleEnthalpy
            >
        > hTabulatedIcoTabulatedSolidThermoPhysics;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
