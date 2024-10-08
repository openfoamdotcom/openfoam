/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2021 OpenCFD Ltd.
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

#include "fixedValue/fixedValue.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace distributionModels
{
    defineTypeNameAndDebug(fixedValue, 0);
    addToRunTimeSelectionTable(distributionModel, fixedValue, dictionary);
}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::distributionModels::fixedValue::fixedValue
(
    const dictionary& dict,
    Random& rndGen
)
:
    distributionModel(typeName, dict, rndGen),
    value_(distributionModelDict_.get<scalar>("value"))
{
    if (value_ < VSMALL)
    {
        FatalErrorInFunction
            << "Fixed value cannot be equal to or less than zero:" << nl
            << "    value = " << value_
            << exit(FatalError);
    }
}


Foam::distributionModels::fixedValue::fixedValue(const fixedValue& p)
:
    distributionModel(p),
    value_(p.value_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::scalar Foam::distributionModels::fixedValue::fixedValue::sample() const
{
    return value_;
}


Foam::scalar Foam::distributionModels::fixedValue::fixedValue::minValue() const
{
    return value_;
}


Foam::scalar Foam::distributionModels::fixedValue::fixedValue::maxValue() const
{
    return value_;
}


Foam::scalar Foam::distributionModels::fixedValue::fixedValue::meanValue() const
{
    return value_;
}


// ************************************************************************* //
