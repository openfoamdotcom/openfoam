/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016 OpenCFD Ltd.
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

#include "db/Time/TimeOpenFOAM.H"
#include "dimensionedTypes/dimensionedType/dimensionedType.H"
#include "finiteVolume/fvc/fvcDdt.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class FieldType>
int Foam::functionObjects::ddt2::apply(const word& inputName, int& state)
{
    // State: return 0 (not-processed), -1 (skip), +1 ok

    // Already done, or not available
    if (state || !foundObject<FieldType>(inputName))
    {
        return state;
    }

    const FieldType& input = lookupObject<FieldType>(inputName);

    word outputName(resultName_);
    outputName.replace("@@", inputName);

    results_.set(outputName);

    if (!foundObject<volScalarField>(outputName))
    {
        const dimensionSet dims =
        (
            mag_
          ? mag(input.dimensions()/dimTime)
          : magSqr(input.dimensions()/dimTime)
        );

        auto tddt2 = tmp<volScalarField>::New
        (
            IOobject
            (
                outputName,
                time_.timeName(),
                mesh_,
                IOobject::NO_READ,
                IOobject::NO_WRITE,
                IOobject::REGISTER
            ),
            mesh_,
            dimensionedScalar(dims, Zero)
        );

        store(outputName, tddt2);
    }

    volScalarField& output = lookupObjectRef<volScalarField>(outputName);

    if (mag_)
    {
        output = mag(fvc::ddt(input));
    }
    else
    {
        output = magSqr(fvc::ddt(input));
    }

    // Could add additional statistics here
    Log << type() << ' ' << name()
        << " field " << outputName
        << " average: " << gAverage(output) << endl;

    state = +1;
    return state;
}


// ************************************************************************* //
