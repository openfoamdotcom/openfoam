/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2018-2020 OpenFOAM Foundation
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

#include "laminar/generalizedNewtonian/generalizedNewtonianViscosityModels/HerschelBulkley/HerschelBulkley.H"
#include "fields/volFields/volFields.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace laminarModels
{
namespace generalizedNewtonianViscosityModels
{
    defineTypeNameAndDebug(HerschelBulkley, 0);

    addToRunTimeSelectionTable
    (
        generalizedNewtonianViscosityModel,
        HerschelBulkley,
        dictionary
    );
}
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::laminarModels::generalizedNewtonianViscosityModels::HerschelBulkley::
HerschelBulkley
(
    const dictionary& viscosityProperties
)
:
    generalizedNewtonianViscosityModel(viscosityProperties),
    HerschelBulkleyCoeffs_
    (
        viscosityProperties.optionalSubDict(typeName + "Coeffs")
    ),
    n_("n", dimless, HerschelBulkleyCoeffs_),
    tau0_("tau0", dimViscosity/dimTime, HerschelBulkleyCoeffs_)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool Foam::laminarModels::generalizedNewtonianViscosityModels::
HerschelBulkley::read
(
    const dictionary& viscosityProperties
)
{
    generalizedNewtonianViscosityModel::read(viscosityProperties);

    HerschelBulkleyCoeffs_ =
        viscosityProperties.optionalSubDict(typeName + "Coeffs");

    HerschelBulkleyCoeffs_.readEntry("n", n_);
    HerschelBulkleyCoeffs_.readEntry("tau0", tau0_);

    return true;
}


Foam::tmp<Foam::volScalarField>
Foam::laminarModels::generalizedNewtonianViscosityModels::HerschelBulkley::
nu
(
    const volScalarField& nu0,
    const volScalarField& strainRate
) const
{
    const dimensionedScalar tone("tone", dimTime, 1);
    const dimensionedScalar rtone("rtone", dimless/dimTime, 1);

    return
    (
        min
        (
            nu0,
            (tau0_ + nu0*rtone*pow(tone*strainRate, n_))
           /max
            (
                strainRate,
                dimensionedScalar("SMALL", dimless/dimTime, VSMALL)
            )
        )
    );
}


// ************************************************************************* //
