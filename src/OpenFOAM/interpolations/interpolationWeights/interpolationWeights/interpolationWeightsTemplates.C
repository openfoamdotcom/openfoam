/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2012-2016 OpenFOAM Foundation
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

\*---------------------------------------------------------------------------*/

#include "interpolations/interpolationWeights/interpolationWeights/interpolationWeights.H"
#include "primitives/VectorSpace/products.H"

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ListType1, class ListType2>
typename Foam::outerProduct
<
    typename ListType1::value_type,
    typename ListType2::value_type
>::type
Foam::interpolationWeights::weightedSum
(
    const ListType1& f1,
    const ListType2& f2
)
{
    typedef typename outerProduct
    <
        typename ListType1::value_type,
        typename ListType2::value_type
    >::type returnType;

    const label len = f1.size();
    if (len)
    {
        returnType SumProd = f1[0]*f2[0];
        for (label i = 1; i < len; ++i)
        {
            SumProd += f1[i]*f2[i];
        }
        return SumProd;
    }

    return Zero;
}


// ************************************************************************* //
