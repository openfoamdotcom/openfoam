/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2017-2018 OpenFOAM Foundation
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

#include "diameterModels/velocityGroup/sizeGroup/sizeGroup.H"
#include "populationBalanceModel/populationBalanceModel/populationBalanceModel.H"
#include "fields/fvPatchFields/basic/mixed/mixedFvPatchField.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::diameterModels::sizeGroup::sizeGroup
(
    const word& name,
    const dictionary& dict,
    const phaseModel& phase,
    const velocityGroup& velocityGroup,
    const fvMesh& mesh
)
:
    volScalarField
    (
        IOobject
        (
            IOobject::groupName
            (
                name,
                IOobject::groupName
                (
                    velocityGroup.phase().name(),
                    velocityGroup.popBalName()
                )
            ),
            mesh.time().timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedScalar(name, dimless, dict.get<scalar>("value")),
        velocityGroup.f().boundaryField().types()
    ),
    phase_(phase),
    velocityGroup_(velocityGroup),
    d_("d", dimLength, dict),
    x_("x", velocityGroup.formFactor()*pow3(d_)),
    value_(dict.get<scalar>("value"))
{
    // Adjust refValue at mixedFvPatchField boundaries
    forAll(this->boundaryField(), patchi)
    {
        typedef mixedFvPatchField<scalar> mixedFvPatchScalarField;

        if
        (
            isA<mixedFvPatchScalarField>(this->boundaryFieldRef()[patchi])
        )
        {
            mixedFvPatchScalarField& f =
                refCast<mixedFvPatchScalarField>
                (
                    this->boundaryFieldRef()[patchi]
                );

            f.refValue() = value_;
        }
    }
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::diameterModels::sizeGroup::~sizeGroup()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::autoPtr<Foam::diameterModels::sizeGroup>
Foam::diameterModels::sizeGroup::clone() const
{
    NotImplemented;
    return nullptr;
}


// ************************************************************************* //
