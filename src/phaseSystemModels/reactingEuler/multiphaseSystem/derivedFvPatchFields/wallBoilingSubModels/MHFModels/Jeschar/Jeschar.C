/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2018-2021 OpenCFD Ltd
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

#include "derivedFvPatchFields/wallBoilingSubModels/MHFModels/Jeschar/Jeschar.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"
#include "fields/UniformDimensionedFields/uniformDimensionedFields.H"
#include "phasePair/phasePairKey.H"
#include "phaseSystem/phaseSystem.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace wallBoilingModels
{
namespace CHFModels
{
    defineTypeNameAndDebug(Jeschar, 0);
    addToRunTimeSelectionTable
    (
        MHFModel,
        Jeschar,
        dictionary
    );
}
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::wallBoilingModels::CHFModels::Jeschar::Jeschar
(
    const dictionary& dict
)
:
    MHFModel(),
    Kmhf_(dict.getOrDefault<scalar>("Kmhf", 0.16))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::tmp<Foam::scalarField>
Foam::wallBoilingModels::CHFModels::Jeschar::MHF
(
    const phaseModel& liquid,
    const phaseModel& vapor,
    const label patchi,
    const scalarField& Tl,
    const scalarField& Tsatw,
    const scalarField& L
) const
{
    const uniformDimensionedVectorField& g =
        liquid.mesh().time().lookupObject<uniformDimensionedVectorField>("g");

    const labelUList& cells = liquid.mesh().boundary()[patchi].faceCells();

    const scalarField& pw = liquid.thermo().p().boundaryField()[patchi];

    tmp<scalarField> trhoVapor = vapor.thermo().rhoEoS(pw, Tsatw, cells);
    const scalarField& rhoVapor = trhoVapor.ref();

    tmp<scalarField> trhoLiq = liquid.thermo().rhoEoS(pw, Tsatw, cells);
    const scalarField& rhoLiq = trhoLiq.ref();

    const phasePairKey pair(liquid.name(), vapor.name());
    const scalarField sigma
    (
        liquid.fluid().sigma(pair)().boundaryField()[patchi]
    );

    return
        Kmhf_*rhoVapor*L
       *(
            pow(sigma/(mag(g.value())*(rhoLiq - rhoVapor)), 0.25)
          * sqrt
            (
                mag(g.value())*(rhoLiq - rhoVapor)/(rhoLiq + rhoVapor + VSMALL)
            )
        );
}


void Foam::wallBoilingModels::CHFModels::Jeschar::write
(
    Ostream& os
) const
{
    MHFModel::write(os);
    os.writeEntry("Kmhf", Kmhf_);
}


// ************************************************************************* //
