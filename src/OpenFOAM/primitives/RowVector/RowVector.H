/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016 OpenFOAM Foundation
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
    Foam::RowVector

Description
    Templated 3D row-vector derived from MatrixSpace adding construction from
    3 components and element access using x(), y() and z().

SourceFiles
    RowVectorI.H

\*---------------------------------------------------------------------------*/

#ifndef RowVector_H
#define RowVector_H

#include "primitives/MatrixSpace/MatrixSpace.H"
#include "primitives/Vector/VectorPascal.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class RowVector Declaration
\*---------------------------------------------------------------------------*/

template<class Cmpt>
class RowVector
:
    public MatrixSpace<RowVector<Cmpt>, Cmpt, 1, 3>
{

public:

    //- Equivalent type of labels used for valid component indexing
    typedef RowVector<label> labelType;


    //- Component labeling enumeration
    enum components { X, Y, Z };


    // Constructors

        //- Default construct
        RowVector() = default;

        //- Construct initialized to zero
        inline RowVector(const Foam::zero);

        //- Construct given VectorSpace of the same rank
        template<class Cmpt2>
        inline RowVector(const MatrixSpace<RowVector<Cmpt2>, Cmpt2, 1, 3>&);

        //- Construct given three components
        inline RowVector(const Cmpt& rvx, const Cmpt& rvy, const Cmpt& rvz);

        //- Construct from Istream
        inline explicit RowVector(Istream&);


    // Member Functions

    // Component Access

        const Cmpt& x() const noexcept { return this->v_[X]; }
        const Cmpt& y() const noexcept { return this->v_[Y]; }
        const Cmpt& z() const noexcept { return this->v_[Z]; }

        Cmpt& x() noexcept { return this->v_[X]; }
        Cmpt& y() noexcept { return this->v_[Y]; }
        Cmpt& z() noexcept { return this->v_[Z]; }
};


template<class Cmpt>
class typeOfTranspose<Cmpt, Vector<Cmpt>>
{
public:

    typedef RowVector<Cmpt> type;
};


template<class Cmpt>
class typeOfTranspose<Cmpt, RowVector<Cmpt>>
{
public:

    typedef Vector<Cmpt> type;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "primitives/RowVector/RowVectorI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
