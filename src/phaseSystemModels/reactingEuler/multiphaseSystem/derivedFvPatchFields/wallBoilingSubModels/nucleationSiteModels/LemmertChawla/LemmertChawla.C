/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016-2018 OpenFOAM Foundation
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

#include "derivedFvPatchFields/wallBoilingSubModels/nucleationSiteModels/LemmertChawla/LemmertChawla.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace wallBoilingModels
{
namespace nucleationSiteModels
{
    defineTypeNameAndDebug(LemmertChawla, 0);
    addToRunTimeSelectionTable
    (
        nucleationSiteModel,
        LemmertChawla,
        dictionary
    );
}
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::wallBoilingModels::nucleationSiteModels::LemmertChawla::LemmertChawla
(
    const dictionary& dict
)
:
    nucleationSiteModel(),
    Cn_(dict.getOrDefault<scalar>("Cn", 1))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::tmp<Foam::scalarField>
Foam::wallBoilingModels::nucleationSiteModels::LemmertChawla::N
(
    const phaseModel& liquid,
    const phaseModel& vapor,
    const label patchi,
    const scalarField& Tl,
    const scalarField& Tsatw,
    const scalarField& L
) const
{
    const fvPatchScalarField& Tw =
        liquid.thermo().T().boundaryField()[patchi];

    return Cn_*9.922e5*pow(max((Tw - Tsatw)/scalar(10), scalar(0)), 1.805);
}


void Foam::wallBoilingModels::nucleationSiteModels::LemmertChawla::write
(
    Ostream& os
) const
{
    nucleationSiteModel::write(os);
    os.writeEntry("Cn", Cn_);
}


// ************************************************************************* //
