/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
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

#include "clouds/Templates/CollidingCloud/CollidingCloud.H"
#include "submodels/Kinematic/CollisionModel/CollisionModel/CollisionModel.H"
#include "submodels/Kinematic/CollisionModel/NoCollision/NoCollision.H"

// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

template<class CloudType>
void Foam::CollidingCloud<CloudType>::setModels()
{
    collisionModel_.reset
    (
        CollisionModel<CollidingCloud<CloudType>>::New
        (
            this->subModelProperties(),
            *this
        ).ptr()
    );
}


template<class CloudType>
template<class TrackCloudType>
void Foam::CollidingCloud<CloudType>::moveCollide
(
    TrackCloudType& cloud,
    typename parcelType::trackingData& td,
    const scalar deltaT
)
{
    td.part() = parcelType::trackingData::tpVelocityHalfStep;
    CloudType::move(cloud, td, deltaT);

    td.part() = parcelType::trackingData::tpLinearTrack;
    CloudType::move(cloud, td, deltaT);

    // td.part() = parcelType::trackingData::tpRotationalTrack;
    // CloudType::move(cloud, td, deltaT);

    this->updateCellOccupancy();

    this->collision().collide();

    td.part() = parcelType::trackingData::tpVelocityHalfStep;
    CloudType::move(cloud, td, deltaT);
}



template<class CloudType>
void Foam::CollidingCloud<CloudType>::cloudReset(CollidingCloud<CloudType>& c)
{
    CloudType::cloudReset(c);

    collisionModel_.reset(c.collisionModel_.ptr());
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
Foam::CollidingCloud<CloudType>::CollidingCloud
(
    const word& cloudName,
    const volScalarField& rho,
    const volVectorField& U,
    const volScalarField& mu,
    const dimensionedVector& g,
    bool readFields
)
:
    CloudType(cloudName, rho, U, mu, g, false),
    constProps_(this->particleProperties()),
    collisionModel_(nullptr)
{
    if (this->solution().active())
    {
        setModels();

        if (readFields)
        {
            parcelType::readFields(*this);
            this->deleteLostParticles();
        }

        if
        (
            this->solution().steadyState()
         && !isType<NoCollision<CollidingCloud<CloudType>>>(collisionModel_())
        )
        {
            FatalErrorInFunction
                << "Collision modelling not currently available "
                << "for steady state calculations" << exit(FatalError);
        }
    }
}


template<class CloudType>
Foam::CollidingCloud<CloudType>::CollidingCloud
(
    CollidingCloud<CloudType>& c,
    const word& name
)
:
    CloudType(c, name),
    collisionModel_(c.collisionModel_->clone())
{}


template<class CloudType>
Foam::CollidingCloud<CloudType>::CollidingCloud
(
    const fvMesh& mesh,
    const word& name,
    const CollidingCloud<CloudType>& c
)
:
    CloudType(mesh, name, c),
    collisionModel_(nullptr)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
Foam::CollidingCloud<CloudType>::~CollidingCloud()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void Foam::CollidingCloud<CloudType>::storeState()
{
    cloudCopyPtr_.reset
    (
        static_cast<CollidingCloud<CloudType>*>
        (
            clone(this->name() + "Copy").ptr()
        )
    );
}


template<class CloudType>
void Foam::CollidingCloud<CloudType>::restoreState()
{
    cloudReset(cloudCopyPtr_());
    cloudCopyPtr_.clear();
}


template<class CloudType>
void Foam::CollidingCloud<CloudType>::evolve()
{
    if (this->solution().canEvolve())
    {
        typename parcelType::trackingData td(*this);

        this->solve(*this, td);
    }
}


template<class CloudType>
template<class TrackCloudType>
void  Foam::CollidingCloud<CloudType>::motion
(
    TrackCloudType& cloud,
    typename parcelType::trackingData& td
)
{
    // Sympletic leapfrog integration of particle forces:
    // + apply half deltaV with stored force
    // + move positions with new velocity
    // + calculate forces in new position
    // + apply half deltaV with new force

    label nSubCycles = collision().nSubCycles();

    if (nSubCycles > 1)
    {
        Log_<< "    " << nSubCycles << " move-collide subCycles" << endl;

        subCycleTime moveCollideSubCycle
        (
            const_cast<Time&>(this->db().time()),
            nSubCycles
        );

        while(!(++moveCollideSubCycle).end())
        {
            moveCollide(cloud, td, this->db().time().deltaTValue());
        }

        moveCollideSubCycle.endSubCycle();
    }
    else
    {
        moveCollide(cloud, td, this->db().time().deltaTValue());
    }
}


template<class CloudType>
void Foam::CollidingCloud<CloudType>::info()
{
    CloudType::info();

    scalar rotationalKineticEnergy = rotationalKineticEnergyOfSystem();
    reduce(rotationalKineticEnergy, sumOp<scalar>());

    Log_<< "    Rotational kinetic energy       = "
        << rotationalKineticEnergy << nl;
}


// ************************************************************************* //
