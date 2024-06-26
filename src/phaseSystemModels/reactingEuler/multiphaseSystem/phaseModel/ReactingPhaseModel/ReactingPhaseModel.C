/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2015-2018 OpenFOAM Foundation
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

#include "phaseModel/ReactingPhaseModel/ReactingPhaseModel.H"
#include "phaseSystem/phaseSystem.H"
#include "fvMatrices/fvMatrix/fvMatrix.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasePhaseModel, class ReactionType>
Foam::ReactingPhaseModel<BasePhaseModel, ReactionType>::ReactingPhaseModel
(
    const phaseSystem& fluid,
    const word& phaseName,
    const label index
)
:
    BasePhaseModel(fluid, phaseName, index),
    reaction_(ReactionType::New(this->thermo_(), this->turbulence_()))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class BasePhaseModel, class ReactionType>
Foam::ReactingPhaseModel<BasePhaseModel, ReactionType>::~ReactingPhaseModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasePhaseModel, class ReactionType>
void Foam::ReactingPhaseModel<BasePhaseModel, ReactionType>::correctThermo()
{
    BasePhaseModel::correctThermo();

    reaction_->correct();
}


template<class BasePhaseModel, class ReactionType>
Foam::tmp<Foam::fvScalarMatrix>
Foam::ReactingPhaseModel<BasePhaseModel, ReactionType>::R
(
    volScalarField& Yi
) const
{
    return reaction_->R(Yi);
}


template<class BasePhaseModel, class ReactionType>
Foam::tmp<Foam::volScalarField>
Foam::ReactingPhaseModel<BasePhaseModel, ReactionType>::Qdot() const
{
    return reaction_->Qdot();
}


// ************************************************************************* //
