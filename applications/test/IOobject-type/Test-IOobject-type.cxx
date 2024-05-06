/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2023 OpenCFD Ltd.
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

Description
    Report global/local path for various types

\*---------------------------------------------------------------------------*/

#include "global/argList/argList.H"
#include "db/Time/TimeOpenFOAM.H"
#include "db/IOobject/IOobject.H"
#include "db/IOobjects/IOdictionary/IOdictionary.H"
#include "db/IOobjects/IOMap/IOMap.H"
#include "primitives/coordinate/systems/coordinateSystems.H"
#include "finiteArea/faSchemes/faSchemes.H"
#include "finiteVolume/fvSchemes/fvSchemes.H"
#include "matrices/schemes/schemesLookup.H"
#include "primitives/Scalar/lists/scalarIOList.H"

using namespace Foam;


template<class Type>
word report()
{
    if (is_globalIOobject<Type>::value)
    {
        return "global";
    }
    else
    {
        return "local";
    }
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Main program:

int main(int argc, char *argv[])
{
    Info<< "void: " << report<void>() << nl;
    Info<< "IOobject: " << report<IOobject>() << nl;
    Info<< "IOdictionary: " << report<IOdictionary>() << nl;
    Info<< "faSchemes: " << report<faSchemes>() << nl;
    Info<< "fvSchemes: " << report<fvSchemes>() << nl;
    Info<< "schemesLookup: " << report<schemesLookup>() << nl;
    Info<< "coordinateSystems: " << report<coordinateSystems>() << nl;
    Info<< "IOMap<labelList>: " << report<IOMap<labelList>>() << nl;
    Info<< "IOMap<dictionary>: " << report<IOMap<dictionary>>() << nl;

    Info<< "\nEnd\n" << endl;

    return 0;
}


// ************************************************************************* //
