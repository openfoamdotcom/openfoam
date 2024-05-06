/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2012-2014 OpenFOAM Foundation
    Copyright (C) 2017-2021 OpenCFD Ltd.
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
    foamHelp

Group
    grpMiscUtilities

Description
    Top level wrapper utility around foam help utilities

\*---------------------------------------------------------------------------*/

#include "cfdTools/general/include/fvCFD.H"
#include "helpType/helpType.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "include/addRegionOption.H"
    #include "addToolOption.H"

    // Intercept request for any -option (eg, -doc, -help)
    // when it is the first argument
    if (argc > 1 && '-' == *argv[1])
    {
        #include "include/setRootCase.H"
    }
    else if (argc < 2)
    {
        FatalError
            << "No help utility has been supplied" << nl
            << exit(FatalError);
    }

    word utilityName(argv[1]);
    autoPtr<helpType> utility;

    const bool oldThrowingErr = FatalError.throwing(true);
    try
    {
        utility.reset(helpType::New(utilityName));
    }
    catch (const Foam::error& err)
    {
        utility.clear();

        FatalError
            << err.message().c_str() << nl
            << exit(FatalError);
    }
    FatalError.throwing(oldThrowingErr);

    utility().init();

    #include "include/setRootCase.H"
    #include "include/createTime.H"
    #include "include/createNamedMesh.H"

    utility().execute(args, mesh);

    Info<< "\nEnd\n" << endl;

    return 0;
}


// ************************************************************************* //
