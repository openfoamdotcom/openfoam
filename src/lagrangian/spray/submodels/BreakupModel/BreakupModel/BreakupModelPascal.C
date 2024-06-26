/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2015 OpenFOAM Foundation
    Copyright (C) 2020 OpenCFD Ltd.
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

#include "submodels/BreakupModel/BreakupModel/BreakupModelPascal.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
Foam::BreakupModel<CloudType>::BreakupModel
(
    CloudType& owner
)
:
    CloudSubModelBase<CloudType>(owner),
    solveOscillationEq_(false),
    y0_(0.0),
    yDot0_(0.0),
    TABComega_(0.0),
    TABCmu_(0.0),
    TABtwoWeCrit_(0.0)
{}


template<class CloudType>
Foam::BreakupModel<CloudType>::BreakupModel
(
    const BreakupModel<CloudType>& bum
)
:
    CloudSubModelBase<CloudType>(bum),
    solveOscillationEq_(bum.solveOscillationEq_),
    y0_(bum.y0_),
    yDot0_(bum.yDot0_),
    TABComega_(bum.TABComega_),
    TABCmu_(bum.TABCmu_),
    TABtwoWeCrit_(bum.TABtwoWeCrit_)
{}


template<class CloudType>
Foam::BreakupModel<CloudType>::BreakupModel
(
    const dictionary& dict,
    CloudType& owner,
    const word& type,
    bool solveOscillationEq
)
:
    CloudSubModelBase<CloudType>(owner, dict, typeName, type),
    solveOscillationEq_(solveOscillationEq),
    y0_(this->coeffDict().template getOrDefault<scalar>("y0", 0)),
    yDot0_(this->coeffDict().template getOrDefault<scalar>("yDot0", 0)),
    TABComega_(8),
    TABCmu_(5),
    TABtwoWeCrit_(12)
{
    if (solveOscillationEq_ && dict.found("TABCoeffs"))
    {
        const dictionary coeffs(dict.subDict("TABCoeffs"));
        coeffs.readEntry("Comega", TABComega_);
        coeffs.readEntry("Cmu", TABCmu_);

        const scalar WeCrit(coeffs.get<scalar>("WeCrit"));
        TABtwoWeCrit_ = 2*WeCrit;
    }
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
Foam::BreakupModel<CloudType>::~BreakupModel()
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "submodels/BreakupModel/BreakupModel/BreakupModelNew.C"

// ************************************************************************* //
