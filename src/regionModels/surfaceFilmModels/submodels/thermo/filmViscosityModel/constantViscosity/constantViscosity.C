/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2013-2017 OpenFOAM Foundation
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

#include "submodels/thermo/filmViscosityModel/constantViscosity/constantViscosity.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace regionModels
{
namespace surfaceFilmModels
{

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(constantViscosity, 0);

addToRunTimeSelectionTable
(
    filmViscosityModel,
    constantViscosity,
    dictionary
);

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

constantViscosity::constantViscosity
(
    surfaceFilmRegionModel& film,
    const dictionary& dict,
    volScalarField& mu
)
:
    filmViscosityModel(typeName, film, dict, mu),
    mu0_("mu0", dimDynamicViscosity, coeffDict_)
{
    mu_ == mu0_;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

constantViscosity::~constantViscosity()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void constantViscosity::correct
(
    const volScalarField& p,
    const volScalarField& T
)
{
    mu_ == mu0_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace surfaceFilmModels
} // End namespace regionModels
} // End namespace Foam

// ************************************************************************* //
