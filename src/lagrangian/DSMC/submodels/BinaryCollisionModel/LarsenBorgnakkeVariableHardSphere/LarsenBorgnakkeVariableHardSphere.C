/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2015 OpenFOAM Foundation
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

#include "submodels/BinaryCollisionModel/LarsenBorgnakkeVariableHardSphere/LarsenBorgnakkeVariableHardSphere.H"
#include "global/constants/constants.H"

using namespace Foam::constant::mathematical;

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class CloudType>
Foam::scalar Foam::LarsenBorgnakkeVariableHardSphere<CloudType>::energyRatio
(
    scalar ChiA,
    scalar ChiB
)
{
    CloudType& cloud(this->owner());

    Random& rndGen = cloud.rndGen();

    scalar ChiAMinusOne = ChiA - 1;
    scalar ChiBMinusOne = ChiB - 1;

    if (ChiAMinusOne < SMALL && ChiBMinusOne < SMALL)
    {
        return rndGen.sample01<scalar>();
    }

    scalar energyRatio;
    scalar P;

    do
    {
        P = 0;

        energyRatio = rndGen.sample01<scalar>();

        if (ChiAMinusOne < SMALL)
        {
            P = 1.0 - pow(energyRatio, ChiB);
        }
        else if (ChiBMinusOne < SMALL)
        {
            P = 1.0 - pow(energyRatio, ChiA);
        }
        else
        {
            P =
                pow
                (
                    (ChiAMinusOne + ChiBMinusOne)*energyRatio/ChiAMinusOne,
                    ChiAMinusOne
                )
               *pow
                (
                    (ChiAMinusOne + ChiBMinusOne)*(1 - energyRatio)
                    /ChiBMinusOne,
                    ChiBMinusOne
                );
        }
    } while (P < rndGen.sample01<scalar>());

    return energyRatio;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
Foam::LarsenBorgnakkeVariableHardSphere<CloudType>::
LarsenBorgnakkeVariableHardSphere
(
    const dictionary& dict,
    CloudType& cloud
)
:
    BinaryCollisionModel<CloudType>(dict, cloud, typeName),
    Tref_(this->coeffDict().getScalar("Tref")),
    relaxationCollisionNumber_
    (
        this->coeffDict().getScalar("relaxationCollisionNumber")
    )
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
Foam::LarsenBorgnakkeVariableHardSphere<CloudType>::
~LarsenBorgnakkeVariableHardSphere()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool Foam::LarsenBorgnakkeVariableHardSphere<CloudType>::active() const
{
    return true;
}


template<class CloudType>
Foam::scalar Foam::LarsenBorgnakkeVariableHardSphere<CloudType>::sigmaTcR
(
    const typename CloudType::parcelType& pP,
    const typename CloudType::parcelType& pQ
) const
{
    const CloudType& cloud(this->owner());

    label typeIdP = pP.typeId();
    label typeIdQ = pQ.typeId();

    scalar dPQ =
        0.5
       *(
            cloud.constProps(typeIdP).d()
          + cloud.constProps(typeIdQ).d()
        );

    scalar omegaPQ =
        0.5
       *(
            cloud.constProps(typeIdP).omega()
          + cloud.constProps(typeIdQ).omega()
        );

    scalar cR = mag(pP.U() - pQ.U());

    if (cR < VSMALL)
    {
        return 0;
    }

    scalar mP = cloud.constProps(typeIdP).mass();
    scalar mQ = cloud.constProps(typeIdQ).mass();
    scalar mR = mP*mQ/(mP + mQ);

    // calculating cross section = pi*dPQ^2, where dPQ is from Bird, eq. 4.79
    scalar sigmaTPQ =
        pi*dPQ*dPQ
       *pow(2.0*physicoChemical::k.value()*Tref_/(mR*cR*cR), omegaPQ - 0.5)
       /exp(Foam::lgamma(2.5 - omegaPQ));

    return sigmaTPQ*cR;
}


template<class CloudType>
void Foam::LarsenBorgnakkeVariableHardSphere<CloudType>::collide
(
    typename CloudType::parcelType& pP,
    typename CloudType::parcelType& pQ
)
{
    CloudType& cloud(this->owner());

    label typeIdP = pP.typeId();
    label typeIdQ = pQ.typeId();
    vector& UP = pP.U();
    vector& UQ = pQ.U();
    scalar& EiP = pP.Ei();
    scalar& EiQ = pQ.Ei();

    Random& rndGen = cloud.rndGen();

    scalar inverseCollisionNumber = 1/relaxationCollisionNumber_;

    // Larsen Borgnakke internal energy redistribution part.  Using the serial
    // application of the LB method, as per the INELRS subroutine in Bird's
    // DSMC0R.FOR

    scalar preCollisionEiP = EiP;
    scalar preCollisionEiQ = EiQ;

    direction iDofP = cloud.constProps(typeIdP).internalDegreesOfFreedom();
    direction iDofQ = cloud.constProps(typeIdQ).internalDegreesOfFreedom();

    scalar omegaPQ =
        0.5
       *(
            cloud.constProps(typeIdP).omega()
          + cloud.constProps(typeIdQ).omega()
        );

    scalar mP = cloud.constProps(typeIdP).mass();
    scalar mQ = cloud.constProps(typeIdQ).mass();
    scalar mR = mP*mQ/(mP + mQ);
    vector Ucm = (mP*UP + mQ*UQ)/(mP + mQ);
    scalar cRsqr = magSqr(UP - UQ);
    scalar availableEnergy = 0.5*mR*cRsqr;
    scalar ChiB = 2.5 - omegaPQ;

    if (iDofP > 0)
    {
        if (inverseCollisionNumber > rndGen.sample01<scalar>())
        {
            availableEnergy += preCollisionEiP;

            if (iDofP == 2)
            {
                scalar energyRatio =
                    1.0 - pow(rndGen.sample01<scalar>(), (1.0/ChiB));
                EiP = energyRatio*availableEnergy;
            }
            else
            {
                scalar ChiA = 0.5*iDofP;
                EiP = energyRatio(ChiA, ChiB)*availableEnergy;
            }

            availableEnergy -= EiP;
        }
    }

    if (iDofQ > 0)
    {
        if (inverseCollisionNumber > rndGen.sample01<scalar>())
        {
            availableEnergy += preCollisionEiQ;

            if (iDofQ == 2)
            {
                const scalar energyRatio =
                    1.0 - pow(rndGen.sample01<scalar>(), (1.0/ChiB));

                EiQ = energyRatio*availableEnergy;
            }
            else
            {
                const scalar ChiA = 0.5*iDofQ;
                EiQ = energyRatio(ChiA, ChiB)*availableEnergy;
            }

            availableEnergy -= EiQ;
        }
    }

    // Rescale the translational energy
    scalar cR = sqrt(2.0*availableEnergy/mR);

    // Variable Hard Sphere collision part
    scalar cosTheta = 2.0*rndGen.sample01<scalar>() - 1.0;
    scalar sinTheta = sqrt(1.0 - cosTheta*cosTheta);
    scalar phi = twoPi*rndGen.sample01<scalar>();

    vector postCollisionRelU =
        cR
       *vector
        (
            cosTheta,
            sinTheta*cos(phi),
            sinTheta*sin(phi)
        );

    UP = Ucm + postCollisionRelU*mQ/(mP + mQ);
    UQ = Ucm - postCollisionRelU*mP/(mP + mQ);
}


// ************************************************************************* //
