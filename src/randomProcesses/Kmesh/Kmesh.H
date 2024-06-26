/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2012 OpenFOAM Foundation
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
    Foam::Kmesh

Description
    Calculate the wavenumber vector field corresponding to the
    space vector field of a finite volume mesh;

SourceFiles
    Kmesh.C

\*---------------------------------------------------------------------------*/

#ifndef Kmesh_H
#define Kmesh_H

#include "fvMesh/fvMesh.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class Kmesh Declaration
\*---------------------------------------------------------------------------*/

class Kmesh
:
    public vectorField
{
    // Private data

        //- Dimensions of box
        vector l_;

        //- Multi-dimensional addressing array
        List<int> nn_;

        //- Maximum wavenumber
        scalar kmax_;


    // Private functions

        //- Return the linear index from the i-j-k indices
        static inline label index
        (
            const label i,
            const label j,
            const label k,
            const UList<int>& nn
        );


public:

    // Constructors

        //- Construct from fvMesh
        Kmesh(const fvMesh&);


    // Member Functions

        // Access

        const vector& sizeOfBox() const
        {
            return l_;
        }

        const List<int>& nn() const
        {
            return nn_;
        }

        scalar max() const
        {
            return kmax_;
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
