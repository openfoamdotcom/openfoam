/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016 OpenFOAM Foundation
    Copyright (C) 2019 OpenCFD Ltd.
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
    Foam::blockVertex

Description
    Define a block vertex.

SourceFiles
    blockVertex.C

\*---------------------------------------------------------------------------*/

#ifndef blockVertex_H
#define blockVertex_H

#include "searchableSurfaces/searchableSurfaces/searchableSurfaces.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class blockVertex Declaration
\*---------------------------------------------------------------------------*/

class blockVertex
{
public:

    //- Runtime type information
    TypeName("blockVertex");


    // Declare run-time constructor selection tables

        declareRunTimeSelectionTable
        (
            autoPtr,
            blockVertex,
            Istream,
            (
                const dictionary& dict,
                const label index,
                const searchableSurfaces& geometry,
                Istream& is
            ),
            (dict, index, geometry, is)
        );


    // Constructors

        //- Default construct
        blockVertex() noexcept = default;

        //- Clone function
        virtual autoPtr<blockVertex> clone() const;

        //- New function which constructs and returns pointer to a blockVertex
        static autoPtr<blockVertex> New
        (
            const dictionary& dict,
            const label index,
            const searchableSurfaces& geometry,
            Istream&
        );

        //- Class used for the read-construction of
        //  PtrLists of blockVertex
        class iNew
        {
            const dictionary& dict_;
            const searchableSurfaces& geometry_;
            mutable label index_;

        public:

            iNew(const dictionary& dict, const searchableSurfaces& geometry)
            :
                dict_(dict),
                geometry_(geometry),
                index_(0)
            {}

            autoPtr<blockVertex> operator()(Istream& is) const
            {
                return blockVertex::New(dict_, index_++, geometry_, is);
            }
        };


    //- Destructor
    virtual ~blockVertex() = default;


    // Member Functions

        virtual operator point() const = 0;

        //- Read vertex index with optional name lookup
        static label read(Istream&, const dictionary&);

        //- Write vertex index with optional name backsubstitution
        static void write(Ostream&, const label, const dictionary&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
