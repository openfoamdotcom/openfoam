/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
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
    Foam::featureEdgeMesh

Description
    edgeMesh + IO.

See also
    Foam::extendedFeatureEdgeMesh

SourceFiles
    featureEdgeMesh.C

\*---------------------------------------------------------------------------*/

#ifndef featureEdgeMesh_H
#define featureEdgeMesh_H

#include "edgeMesh/edgeMesh.H"
#include "db/regIOobject/regIOobject.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class featureEdgeMesh Declaration
\*---------------------------------------------------------------------------*/

class featureEdgeMesh
:
    public regIOobject,
    public edgeMesh
{
public:

    TypeName("featureEdgeMesh");


    // Constructors

        //- Construct (read) given an IOobject
        explicit featureEdgeMesh(const IOobject&);

        //- Construct from featureEdgeMesh data
        featureEdgeMesh
        (
            const IOobject& io,
            const pointField& points,
            const edgeList& edges
        );

        //- Construct as copy
        featureEdgeMesh(const IOobject& io, const edgeMesh& em);


    // IO

        //- ReadData function required for regIOobject read operation
        virtual bool readData(Istream&);

        //- WriteData function required for regIOobject write operation
        virtual bool writeData(Ostream&) const;

        //- Is object global
        virtual bool global() const
        {
            return true;
        }

        //- Return complete path + object name if the file exists
        //  either in the case/processor or case otherwise null
        virtual fileName filePath() const
        {
            return globalFilePath(type());
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//- Global file type for featureEdgeMesh
template<>
struct is_globalIOobject<featureEdgeMesh> : std::true_type {};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
