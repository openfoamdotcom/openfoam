/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
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

#include "submodels/ReactingMultiphase/DevolatilisationModel/DevolatilisationModel/DevolatilisationModel.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
Foam::DevolatilisationModel<CloudType>::DevolatilisationModel
(
    CloudType& owner
)
:
    CloudSubModelBase<CloudType>(owner),
    dMass_(0.0)
{}


template<class CloudType>
Foam::DevolatilisationModel<CloudType>::DevolatilisationModel
(
    const dictionary& dict,
    CloudType& owner,
    const word& type
)
:
    CloudSubModelBase<CloudType>(owner, dict, typeName, type),
    dMass_(0.0)
{}


template<class CloudType>
Foam::DevolatilisationModel<CloudType>::DevolatilisationModel
(
    const DevolatilisationModel<CloudType>& dm
)
:
    CloudSubModelBase<CloudType>(dm),
    dMass_(dm.dMass_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
Foam::DevolatilisationModel<CloudType>::~DevolatilisationModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void Foam::DevolatilisationModel<CloudType>::addToDevolatilisationMass
(
    const scalar dMass
)
{
    dMass_ += dMass;
}


template<class CloudType>
void Foam::DevolatilisationModel<CloudType>::info()
{
    CloudSubModelBase<CloudType>::info();

    const scalar mass0 = this->template getBaseProperty<scalar>("mass");
    const scalar massTotal = mass0 + returnReduce(dMass_, sumOp<scalar>());

    Log_<< "    Mass transfer devolatilisation  = " << massTotal << nl;

    if (this->writeTime())
    {
        this->setBaseProperty("mass", massTotal);
        dMass_ = 0.0;
    }
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "submodels/ReactingMultiphase/DevolatilisationModel/DevolatilisationModel/DevolatilisationModelNew.C"

// ************************************************************************* //
