/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2018-2019 OpenCFD Ltd.
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

Application
    Test-contiguous

Description
    Simple test of contiguous data

\*---------------------------------------------------------------------------*/

#include "include/OSspecific.H"
#include "global/argList/argList.H"
#include "primitives/strings/wordRes/wordRes.H"
#include "primitives/traits/contiguous.H"

#include "db/IOstreams/IOstreams.H"
#include "primitives/Scalar/scalar/scalar.H"
#include "primitives/Vector/floats/vector.H"
#include "primitives/bools/Switch/Switch.H"

#include "primitives/ranges/labelRange/labelRange.H"
#include "primitives/Scalar/lists/scalarList.H"
#include "containers/HashTables/HashOps/HashOps.H"
#include "containers/Lists/FixedList/FixedList.H"
#include "primitives/tuples/Pair.H"

#include "distributedTriSurfaceMesh/distributedTriSurfaceMesh.H"

namespace Foam
{

// Wrong, but interesting to test
template<> struct is_contiguous<Pair<word>> : std::true_type {};

} // end namespace Foam

using namespace Foam;


template<class T>
void printInfo(const char* const name = nullptr)
{
    if (name == nullptr)
    {
        Info<< typeid(T).name();
    }
    else
    {
        Info<< name;
    }

    Info<< " contiguous=" <<  Switch(is_contiguous<T>::value);

    if (is_contiguous_label<T>::value)
    {
        Info<< " label";
    }
    if (is_contiguous_scalar<T>::value)
    {
        Info<< " scalar";
    }

    Info<< nl;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//  Main program:

int main(int argc, char *argv[])
{
    argList::noBanner();
    argList::noParallel();
    argList::noFunctionObjects();

    printInfo<label>();
    printInfo<double>();
    printInfo<FixedList<double, 4>>();
    printInfo<Pair<long>>();

    printInfo<FixedList<word, 2>>();
    printInfo<Pair<word>>();

    printInfo<std::pair<int, vector>>();

    printInfo<FixedList<FixedList<int, 2>, 2>>();
    printInfo<segment>();

    return 0;
}

// ************************************************************************* //
