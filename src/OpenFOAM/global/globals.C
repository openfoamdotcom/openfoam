/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011 OpenFOAM Foundation
    Copyright (C) 2018-2020 OpenCFD Ltd.
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
    Define the globals used in the OpenFOAM library.
    It is important that these are constructed in the appropriate order to
    avoid the use of unconstructed data in the global namespace.

\*---------------------------------------------------------------------------*/

#include <new>
#include <iostream>
#include <cstdlib>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Setup an error handler for the global new operator

namespace Foam
{

void newError()
{
    std::cerr<<
        "new cannot satisfy memory request.\n"
        "This does not necessarily mean you have run out of virtual memory.\n"
        "It could be due to a stack violation caused "
        "by e.g. bad use of pointers or an out-of-date shared library"
        << std::endl;

    std::abort();
}

void (*old_new_handler)() = std::set_new_handler(newError);

} // End namespace Foam


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// The nullObject singleton and a dummy zero singleton

#include "primitives/nullObject/nullObject.C"
#include "primitives/traits/zero.C"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Global IO streams

#include "db/IOstreams/IOstreams.C"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "global/JobInfo/JobInfo.H"
bool Foam::JobInfo::constructed(false);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Global error definitions (initialised by construction)

#include "db/error/messageStream.C"
#include "db/error/error.C"
#include "db/error/IOerror.C"
#include "db/IOstreams/token/token.C"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Read the debug and info switches

#include "global/debug/debug.C"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Read file modification checking switches

#include "db/regIOobject/regIOobject.C"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Read parallel communication switches

#include "db/IOstreams/Pstreams/UPstream.C"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Read constants

#include "global/constants/constants.C"
#include "global/constants/dimensionedConstants.C"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Create the jobInfo file in the $FOAM_JOB_DIR/runningJobs directory

#include "global/JobInfo/JobInfo.C"

// ************************************************************************* //
