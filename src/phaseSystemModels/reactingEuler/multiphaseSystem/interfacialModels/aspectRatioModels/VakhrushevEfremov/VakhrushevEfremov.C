/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2014-2018 OpenFOAM Foundation
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

#include "interfacialModels/aspectRatioModels/VakhrushevEfremov/VakhrushevEfremov.H"
#include "phasePair/reactingEuler_phasePair.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace aspectRatioModels
{
    defineTypeNameAndDebug(VakhrushevEfremov, 0);
    addToRunTimeSelectionTable
    (
        aspectRatioModel,
        VakhrushevEfremov,
        dictionary
    );
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::aspectRatioModels::VakhrushevEfremov::VakhrushevEfremov
(
    const dictionary& dict,
    const phasePair& pair
)
:
    aspectRatioModel(dict, pair)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::aspectRatioModels::VakhrushevEfremov::~VakhrushevEfremov()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Foam::tmp<Foam::volScalarField>
Foam::aspectRatioModels::VakhrushevEfremov::E() const
{
    volScalarField Ta(pair_.Ta());

    return
        neg(Ta - scalar(1))*scalar(1)
      + pos0(Ta - scalar(1))*neg(Ta - scalar(39.8))
       *pow3(0.81 + 0.206*tanh(1.6 - 2*log10(max(Ta, scalar(1)))))
      + pos0(Ta - scalar(39.8))*0.24;
}


// ************************************************************************* //
