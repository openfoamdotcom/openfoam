/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2013-2015 OpenFOAM Foundation
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

InClass
    Foam::basicSolidChemistryModel

Description
    Creates solid chemistry model instances templated on the type of
    solid thermodynamics

\*---------------------------------------------------------------------------*/

#include "makeSolidChemistryModel.H"

#include "pyrolysisChemistryModel/pyrolysisChemistryModel.H"
#include "basicSolidChemistryModel/basicSolidChemistryModel.H"
#include "solidChemistryModel/solidChemistryModel.H"
#include "include/solidThermoPhysicsTypes.H"
#include "include/thermoPhysicsTypes.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// hConstSolidThermoPhysics

makeSolidChemistryModel
(
    solidChemistryModel,
    pyrolysisChemistryModel,
    basicSolidChemistryModel,
    hConstSolidThermoPhysics
);

makeSolidGasChemistryModel
(
    solidChemistryModel,
    pyrolysisChemistryModel,
    basicSolidChemistryModel,
    hConstSolidThermoPhysics,
    gasHThermoPhysics
);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// hPowerSolidThermoPhysics

makeSolidChemistryModel
(
    solidChemistryModel,
    pyrolysisChemistryModel,
    basicSolidChemistryModel,
    hPowerSolidThermoPhysics
);

makeSolidGasChemistryModel
(
    solidChemistryModel,
    pyrolysisChemistryModel,
    basicSolidChemistryModel,
    hPowerSolidThermoPhysics,
    gasHThermoPhysics
);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// hExpKappaConstSolidThermoPhysics

makeSolidChemistryModel
(
    solidChemistryModel,
    pyrolysisChemistryModel,
    basicSolidChemistryModel,
    hExpKappaConstSolidThermoPhysics
);

makeSolidGasChemistryModel
(
    solidChemistryModel,
    pyrolysisChemistryModel,
    basicSolidChemistryModel,
    hExpKappaConstSolidThermoPhysics,
    gasHThermoPhysics
);


// ************************************************************************* //
