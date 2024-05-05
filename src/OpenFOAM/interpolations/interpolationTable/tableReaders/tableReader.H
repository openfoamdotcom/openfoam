/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2020 OpenCFD Ltd.
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

Class
    Foam::tableReader

Description
    Base class to read table data for the interpolationTable

SourceFiles
    tableReader.C

\*---------------------------------------------------------------------------*/

#ifndef tableReader_H
#define tableReader_H

#include "primitives/strings/fileName/fileName.H"
#include "primitives/strings/lists/wordList.H"
#include "primitives/Vector/floats/vector.H"
#include "primitives/Tensor/floats/tensor.H"
#include "db/typeInfo/typeInfo.H"
#include "db/runTimeSelection/construction/runTimeSelectionTables.H"
#include "memory/autoPtr/autoPtr.H"
#include "db/dictionary/dictionary.H"
#include "primitives/tuples/Tuple2.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class tableReader Declaration
\*---------------------------------------------------------------------------*/

template<class Type>
class tableReader
{
public:

    //- Declare type-name, virtual type (with debug switch)
    TypeName("tableReader");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            tableReader,
            dictionary,
            (const dictionary& dict),
            (dict)
        );


    // Constructors

        //- Default construct
        tableReader() = default;

        //- Construct from dictionary
        tableReader(const dictionary& dict);

        //- Construct and return a clone
        virtual autoPtr<tableReader<Type>> clone() const = 0;


    // Selectors

        //- Return a reference to the selected tableReader
        static autoPtr<tableReader> New(const dictionary& spec);


    //- Destructor
    virtual ~tableReader() = default;


    // Member Functions

        //- Read 1D table
        virtual void operator()
        (
            const fileName& fName,
            List<Tuple2<scalar, Type>>& data
        ) = 0;

        //- Read 2D table
        virtual void operator()
        (
            const fileName& fName,
            List<Tuple2<scalar, List<Tuple2<scalar, Type>>>>& tbl
        ) = 0;

        //- Write additional information
        virtual void write(Ostream& os) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "interpolations/interpolationTable/tableReaders/tableReader.C"
#endif


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
