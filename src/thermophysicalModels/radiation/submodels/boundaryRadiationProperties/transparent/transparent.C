/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2018 OpenCFD Ltd.
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

#include "submodels/boundaryRadiationProperties/transparent/transparent.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    namespace radiation
    {
        defineTypeNameAndDebug(transparent, 0);
        addToRunTimeSelectionTable
        (
            boundaryRadiationPropertiesPatch,
            transparent,
            dictionary
        );
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::radiation::transparent::transparent
(
    const dictionary& dict,
    const polyPatch& pp
)
:
    boundaryRadiationPropertiesPatch(dict, pp),
    pp_(pp)
{
    const dictionary& absorptionDict =
        dict.subDict("wallAbsorptionEmissionModel");

    absorptionEmission_.reset
    (
        wallAbsorptionEmissionModel::New(absorptionDict, pp).ptr()
    );

}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::tmp<Foam::scalarField> Foam::radiation::transparent::e
(
    const label bandI,
    vectorField* dir,
    scalarField* T
) const
{
    return(absorptionEmission_->e(bandI, dir, T));
}


Foam::scalar Foam::radiation::transparent::e
(
    const label faceI,
    const label bandI,
    const vector& dir,
    const scalar T
) const
{
    return(absorptionEmission_->e(faceI, bandI, dir, T));
}


Foam::tmp<Foam::scalarField>
Foam::radiation::transparent::a
(
    const label bandI,
    vectorField* dir,
    scalarField* T
) const
{
    return(absorptionEmission_->a(bandI, dir, T));
}


Foam::scalar Foam::radiation::transparent::a
(
    const label faceI,
    const label bandI,
    const vector& dir,
    const scalar T
) const
{
    return(absorptionEmission_->a(faceI, bandI, dir, T));
}


Foam::tmp<Foam::scalarField> Foam::radiation::transparent::t
(
    const label bandI,
    vectorField* dir,
    scalarField* T
) const
{
    return tmp<scalarField>::New(pp_.size(), 1.0);
}


Foam::scalar Foam::radiation::transparent::t
(
    const label faceI,
    const label bandI,
    const vector& dir,
    const scalar T
) const
{
    return 1;
}


Foam::tmp<Foam::scalarField>
Foam::radiation::transparent::rSpec
(
    const label bandI,
    vectorField* dir,
    scalarField* T
) const
{
    return tmp<scalarField>::New(pp_.size(), Zero);
}


Foam::scalar Foam::radiation::transparent::rSpec
(
    const label faceI,
    const label bandI,
    const vector& dir,
    const scalar T
) const
{
    return Zero;
}


Foam::tmp<Foam::scalarField>
Foam::radiation::transparent::rDiff
(
    const label bandI,
    vectorField* dir,
    scalarField* T
) const
{
    return tmp<scalarField>::New(pp_.size(), Zero);
}


Foam::scalar Foam::radiation::transparent::rDiff
(
    const label faceI,
    const label bandI,
    const vector& dir,
    const scalar T
) const
{
    return Zero;
}


bool Foam::radiation::transparent::isGrey() const
{
    return absorptionEmission_->isGrey();
}


Foam::label Foam::radiation::transparent::nBands() const
{
    return absorptionEmission_->nBands();
}


// ************************************************************************* //
