/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2020-2021 OpenCFD Ltd.
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

#include "sources/derived/rotorDiskSource/bladeModel/bladeModel.H"
#include "global/constants/unitConversion.H"
#include "primitives/tuples/Tuple2.H"
#include "primitives/Vector/floats/vector.H"
#include "db/IOstreams/Fstreams/IFstream.H"

// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

bool Foam::bladeModel::readFromFile() const
{
    return !fName_.empty();
}


void Foam::bladeModel::interpolateWeights
(
    const scalar& xIn,
    const List<scalar>& values,
    label& i1,
    label& i2,
    scalar& ddx
) const
{
    i2 = 0;
    label nElem = values.size();

    if (nElem == 1)
    {
        i1 = i2;
        ddx = 0.0;
        return;
    }
    else
    {
        while ((i2 < nElem) && (values[i2] < xIn))
        {
            i2++;
        }

        if (i2 == 0)
        {
            i1 = i2;
            ddx = 0.0;
            return;
        }
        else if (i2 == nElem)
        {
            i2 = nElem - 1;
            i1 = i2;
            ddx = 0.0;
            return;
        }
        else
        {
            i1 = i2 - 1;
            ddx = (xIn - values[i1])/(values[i2] - values[i1]);
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::bladeModel::bladeModel(const dictionary& dict)
:
    profileName_(),
    profileID_(),
    radius_(),
    twist_(),
    chord_(),
    fName_()
{
    List<Tuple2<word, vector>> data;
    if (readFromFile())
    {
        IFstream is(fName_);
        is  >> data;
    }
    else
    {
        dict.readEntry("data", data);
    }

    if (data.size())
    {
        profileName_.setSize(data.size());
        profileID_.setSize(data.size());
        radius_.setSize(data.size());
        twist_.setSize(data.size());
        chord_.setSize(data.size());

        forAll(data, i)
        {
            profileName_[i] = data[i].first();
            profileID_[i] = -1;
            radius_[i] = data[i].second()[0];
            twist_[i] = degToRad(data[i].second()[1]);
            chord_[i] = data[i].second()[2];
        }
    }
    else
    {
        FatalIOErrorInFunction(dict)
            << "No blade data specified"
            << exit(FatalIOError);
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const Foam::List<Foam::word>& Foam::bladeModel::profileName() const
{
    return profileName_;
}


const Foam::List<Foam::label>& Foam::bladeModel::profileID() const
{
    return profileID_;
}


const Foam::List<Foam::scalar>& Foam::bladeModel::radius() const
{
    return radius_;
}


const Foam::List<Foam::scalar>& Foam::bladeModel::twist() const
{
    return twist_;
}


const Foam::List<Foam::scalar>& Foam::bladeModel::chord() const
{
    return chord_;
}


Foam::List<Foam::label>& Foam::bladeModel::profileID()
{
    return profileID_;
}


void Foam::bladeModel::interpolate
(
    const scalar radius,
    scalar& twist,
    scalar& chord,
    label& i1,
    label& i2,
    scalar& invDr
) const
{
    interpolateWeights(radius, radius_, i1, i2, invDr);

    twist = invDr*(twist_[i2] - twist_[i1]) + twist_[i1];
    chord = invDr*(chord_[i2] - chord_[i1]) + chord_[i1];
}


// ************************************************************************* //
