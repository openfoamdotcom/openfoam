/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2015 OpenFOAM Foundation
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

#include "submodels/Thermodynamic/HeatTransferModel/HeatTransferModel/HeatTransferModelPascal.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
Foam::HeatTransferModel<CloudType>::HeatTransferModel(CloudType& owner)
:
    CloudSubModelBase<CloudType>(owner),
    BirdCorrection_(false)
{}


template<class CloudType>
Foam::HeatTransferModel<CloudType>::HeatTransferModel
(
    const dictionary& dict,
    CloudType& owner,
    const word& type
)
:
    CloudSubModelBase<CloudType>(owner, dict, typeName, type),
    BirdCorrection_(this->coeffDict().template get<Switch>("BirdCorrection"))
{}


template<class CloudType>
Foam::HeatTransferModel<CloudType>::HeatTransferModel
(
    const HeatTransferModel<CloudType>& htm
)
:
    CloudSubModelBase<CloudType>(htm),
    BirdCorrection_(htm.BirdCorrection_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
Foam::scalar Foam::HeatTransferModel<CloudType>::htc
(
    const scalar dp,
    const scalar Re,
    const scalar Pr,
    const scalar kappa,
    const scalar NCpW
) const
{
    const scalar Nu = this->Nu(Re, Pr);

    scalar htc = Nu*kappa/dp;

    if (BirdCorrection_ && (mag(htc) > ROOTVSMALL) && (mag(NCpW) > ROOTVSMALL))
    {
        const scalar phit = min(NCpW/htc, 50);
        if (phit > 0.001)
        {
            htc *= phit/(exp(phit) - 1.0);
        }
    }

    return htc;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "submodels/Thermodynamic/HeatTransferModel/HeatTransferModel/HeatTransferModelNewPascal.C"

// ************************************************************************* //
