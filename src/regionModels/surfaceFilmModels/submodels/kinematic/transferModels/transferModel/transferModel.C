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

#include "submodels/kinematic/transferModels/transferModel/transferModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace regionModels
{
namespace surfaceFilmModels
{

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(transferModel, 0);
defineRunTimeSelectionTable(transferModel, dictionary);

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void transferModel::addToTransferredMass(const scalar dMass)
{
    transferredMass_ += dMass;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

transferModel::transferModel(surfaceFilmRegionModel& film)
:
    filmSubModelBase(film),
    transferredMass_(0.0)
{}


transferModel::transferModel
(
    const word& modelType,
    surfaceFilmRegionModel& film,
    const dictionary& dict
)
:
    filmSubModelBase(film, dict, typeName, modelType),
    transferredMass_(0)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

transferModel::~transferModel()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void transferModel::correct()
{
    if (writeTime())
    {
        scalar transferredMass0 = getModelProperty<scalar>("transferredMass");
        transferredMass0 += returnReduce(transferredMass_, sumOp<scalar>());
        setModelProperty<scalar>("transferredMass", transferredMass0);
        transferredMass_ = 0.0;
    }
}

void transferModel::correct
(
    scalarField& availableMass,
    scalarField& massToTransfer,
    scalarField& energyToTransfer
)
{
    scalarField massToTransfer0(massToTransfer.size(), Zero);
    correct(availableMass, massToTransfer0);
    massToTransfer += massToTransfer0;
    energyToTransfer += massToTransfer0*film().hs();
}

scalar transferModel::transferredMassTotal() const
{
    scalar transferredMass0 = getModelProperty<scalar>("transferredMass");
    return transferredMass0 + returnReduce(transferredMass_, sumOp<scalar>());
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace surfaceFilmModels
} // End namespace regionModels
} // End namespace Foam

// ************************************************************************* //
