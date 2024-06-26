/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
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

#include "db/regIOobject/regIOobject.H"
#include "db/Time/TimeOpenFOAM.H"
#include "db/IOstreams/Fstreams/OFstream.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

bool Foam::regIOobject::writeObject
(
    IOstreamOption streamOpt,
    const bool writeOnProc
) const
{
    if (!good())
    {
        SeriousErrorInFunction
            << "bad object " << name() << endl;

        return false;
    }

    if (instance().empty())
    {
        SeriousErrorInFunction
            << "instance undefined for object " << name() << endl;

        return false;
    }


    //- uncomment this if you want to write global objects on master only
    //bool isGlobal = global();
    bool isGlobal = false;

    if (instance() == time().timeName())
    {
        // Mark as written to local directory
        isGlobal = false;
    }
    else if
    (
        instance() != time().system()
     && instance() != time().caseSystem()
     && instance() != time().constant()
     && instance() != time().caseConstant()
    )
    {
        // Update instance
        const_cast<regIOobject&>(*this).instance() = time().timeName();

        // Mark as written to local directory
        isGlobal = false;
    }

    if (OFstream::debug)
    {
        if (isGlobal)
        {
            Pout<< "regIOobject::write() : "
                << "writing (global) file " << objectPath();
        }
        else
        {
            Pout<< "regIOobject::write() : "
                << "writing (local) file " << objectPath();
        }
    }


    // Everyone or just master
    const bool masterOnly
    (
        isGlobal
     && (
            IOobject::fileModificationChecking == IOobject::timeStampMaster
         || IOobject::fileModificationChecking == IOobject::inotifyMaster
        )
    );

    bool osGood = false;
    if (!masterOnly || UPstream::master())
    {
        osGood = fileHandler().writeObject(*this, streamOpt, writeOnProc);
    }
    else
    {
        // Or scatter the master osGood?
        osGood = true;
    }

    if (OFstream::debug)
    {
        Pout<< " .... written" << endl;
    }

    // Only update the lastModified_ time if this object is re-readable,
    // i.e. lastModified_ is already set
    if (!watchIndices_.empty())
    {
        fileHandler().setUnmodified(watchIndices_.back());
    }

    return osGood;
}


bool Foam::regIOobject::write(const bool writeOnProc) const
{
    return writeObject
    (
        IOstreamOption(time().writeFormat(), time().writeCompression()),
        writeOnProc
    );
}


// ************************************************************************* //
