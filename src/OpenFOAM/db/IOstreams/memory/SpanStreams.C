/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2017-2023 OpenCFD Ltd.
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

#include "db/IOstreams/memory/SpanStream.H"
#include "db/IOstreams/memory/OCountStream.H"

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::ISpanStream::print(Ostream& os) const
{
    os  << "ISpanStream: ";
    stream_.debug_info(os);
    os  << Foam::endl;
}


void Foam::OSpanStream::print(Ostream& os) const
{
    os  << "OSpanStream: ";
    stream_.debug_info(os);
    os  << Foam::endl;
}


void Foam::ICharStream::print(Ostream& os) const
{
    os  << "ICharStream: ";
    stream_.debug_info(os);
    os  << Foam::endl;
}


void Foam::OCharStream::print(Ostream& os) const
{
    os  << "OCharStream: ";
    stream_.debug_info(os);
    os  << Foam::endl;
}


void Foam::OCountStream::print(Ostream& os) const
{
    os  << "OCountStream: ";
    // os  << "count=" << stream_.count();
    stream_.debug_info(os);
    os  << Foam::endl;
}


// ************************************************************************* //
