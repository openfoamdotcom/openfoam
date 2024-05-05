/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2014 OpenFOAM Foundation
    Copyright (C) 2015-2023 OpenCFD Ltd.
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

#include "writers/ensight/ensightSurfaceWriter.H"
#include "db/IOstreams/IOstreams/IOmanip.H"
#include "db/IOstreams/Fstreams/Fstream.H"
#include "include/OSspecific.H"
#include "ensight/file/ensightCase.H"
#include "ensight/output/ensightOutput.H"
#include "ensight/part/surface/ensightOutputSurface.H"
#include "ensight/type/ensightPTraits.H"
#include "writers/common/surfaceWriterMethods.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace surfaceWriters
{
    defineTypeName(ensightWriter);
    addToRunTimeSelectionTable(surfaceWriter, ensightWriter, word);
    addToRunTimeSelectionTable(surfaceWriter, ensightWriter, wordDict);
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::surfaceWriters::ensightWriter::ensightWriter()
:
    surfaceWriter(),
    caseOpts_(IOstreamOption::BINARY),
    collateTimes_(true),
    caching_("fieldsDict")  // Historic name
{}


Foam::surfaceWriters::ensightWriter::ensightWriter
(
    const dictionary& options
)
:
    surfaceWriter(options),
    caseOpts_("format", options, IOstreamOption::BINARY),
    collateTimes_(options.getOrDefault("collateTimes", true)),
    caching_("fieldsDict")  // Historic name
{
    caseOpts_.timeFormat("timeFormat", options);
    caseOpts_.timePrecision("timePrecision", options);
}


Foam::surfaceWriters::ensightWriter::ensightWriter
(
    const meshedSurf& surf,
    const fileName& outputPath,
    bool parallel,
    const dictionary& options
)
:
    ensightWriter(options)
{
    open(surf, outputPath, parallel);
}


Foam::surfaceWriters::ensightWriter::ensightWriter
(
    const pointField& points,
    const faceList& faces,
    const fileName& outputPath,
    bool parallel,
    const dictionary& options
)
:
    ensightWriter(options)
{
    open(points, faces, outputPath, parallel);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::surfaceWriters::ensightWriter::close()
{
    caching_.clear();
    surfaceWriter::close();
}


// Note that ensight does supports geometry in a separate file,
// but setting this true leaves geometry files in the wrong places
// (when there are fields).
//
// Make this false to let the field writers take back control
bool Foam::surfaceWriters::ensightWriter::separateGeometry() const
{
    return false;
}


Foam::fileName Foam::surfaceWriters::ensightWriter::write()
{
    // if (collateTimes_)
    // {
    //     return writeCollated();
    // }
    // else
    // {
    //     return writeUncollated();
    // }

    return writeUncollated();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "writers/ensight/ensightSurfaceWriterCollated.C"
#include "writers/ensight/ensightSurfaceWriterUncollated.C"


// Field writing implementations

template<class Type>
Foam::fileName Foam::surfaceWriters::ensightWriter::writeTemplate
(
    const word& fieldName,
    const Field<Type>& localValues
)
{
    if (collateTimes_)
    {
        return writeCollated(fieldName, localValues);
    }
    else
    {
        return writeUncollated(fieldName, localValues);
    }
}


defineSurfaceWriterWriteFields(Foam::surfaceWriters::ensightWriter);


// ************************************************************************* //
