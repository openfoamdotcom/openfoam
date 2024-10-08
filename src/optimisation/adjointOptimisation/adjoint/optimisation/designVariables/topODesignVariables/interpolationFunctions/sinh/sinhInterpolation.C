/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Interpolation CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2020-2023 PCOpt/NTUA
    Copyright (C) 2020-2023 FOSS GP
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

#include "optimisation/designVariables/topODesignVariables/interpolationFunctions/sinh/sinhInterpolation.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(sinhInterpolation, 0);
    addToRunTimeSelectionTable
    (
        topOInterpolationFunction,
        sinhInterpolation,
        dictionary
    );
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::sinhInterpolation::sinhInterpolation
(
    const fvMesh& mesh,
    const dictionary& dict
)
:
    topOInterpolationFunction(mesh, dict),
    b_(Function1<scalar>::New("b",dict))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::sinhInterpolation::interpolate
(
    const scalarField& arg,
    scalarField& res
) const
{
    const scalar time(mesh_.time().timeOutputValue());
    const scalar t(time == 0 ? 1. : time);
    const scalar b(b_->value(t));

    res = scalar(1) - sinh(b*(scalar(1) - arg))/sinh(b);
}


Foam::tmp<Foam::scalarField>
Foam::sinhInterpolation::derivative(const scalarField& arg) const
{
    tmp<scalarField> tderiv(tmp<scalarField>::New(arg.size(), Zero));
    scalarField& deriv = tderiv.ref();

    const scalar t(mesh_.time().timeOutputValue());
    const scalar b(b_->value(t));

    deriv = b*cosh(b*(scalar(1) - arg))/sinh(b);

    return tderiv;
}


// ************************************************************************* //
