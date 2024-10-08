/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2017 OpenFOAM Foundation
    Copyright (C) 2021 OpenCFD Ltd.
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
    Test-decomposedBlockData

Description
    Convert decomposedBlockData into its components.

\*---------------------------------------------------------------------------*/

#include "global/argList/argList.H"
#include "db/Time/TimeOpenFOAM.H"
#include "db/IOobjects/decomposedBlockData/decomposedBlockData.H"
#include "db/IOstreams/Fstreams/OFstream.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//  Main program:

int main(int argc, char *argv[])
{
    argList::addArgument("file");
    #include "include/setRootCase.H"

    if (!Pstream::parRun())
    {
        FatalErrorInFunction
            << "Run in parallel" << exit(FatalError);
    }

    #include "include/createTime.H"

    const auto file = args.get<fileName>(1);

    Info<< "Reading " << file << nl << endl;
    decomposedBlockData data
    (
        UPstream::worldComm,
        IOobject
        (
            file,
            runTime,
            IOobject::MUST_READ,
            IOobject::NO_WRITE,
            IOobject::NO_REGISTER
        )
    );

    data.rename(data.name() + "Data");
    fileName objPath(data.objectPath());
    mkDir(objPath.path());
    Info<< "Opening output file " << objPath << nl << endl;
    OFstream os
    (
        objPath,
        IOstreamOption::BINARY,
        runTime.writeCompression()
    );
    if (!os.good())
    {
        FatalErrorInFunction
            << "Failed opening " << objPath << exit(FatalError);
    }

    if (!data.writeData(os))
    {
        FatalErrorInFunction
            << "Failed writing " << objPath << exit(FatalError);
    }

    return 0;
}


// ************************************************************************* //
