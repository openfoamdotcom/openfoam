/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2017 OpenFOAM Foundation
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
#include "rhoThermo/heRhoThermo.H"
#include "mixtures/pureMixture/pureMixture.H"
#include "thermo/thermo/thermo.H"
#include "thermo/sensibleInternalEnergy/sensibleInternalEnergy.H"
#include "thermo/sensibleEnthalpy/sensibleEnthalpy.H"
#include "thermophysicalPropertiesSelector/thermophysicalPropertiesSelector.H"
#include "liquidProperties/liquidProperties/liquidProperties.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/* * * * * * * * * * * * * * * private static data * * * * * * * * * * * * * */

typedef heRhoThermo
<
    rhoThermo,
    pureMixture
    <
        species::thermo
        <
            thermophysicalPropertiesSelector<liquidProperties>,
            sensibleInternalEnergy
        >
    >
> heRhoThermopureMixtureliquidProperties;


typedef heRhoThermo
<
    rhoThermo,
    pureMixture
    <
        species::thermo
        <
            thermophysicalPropertiesSelector<liquidProperties>,
            sensibleEnthalpy
        >
    >
> heRhoThermopureMixtureEnthalpyliquidProperties;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
