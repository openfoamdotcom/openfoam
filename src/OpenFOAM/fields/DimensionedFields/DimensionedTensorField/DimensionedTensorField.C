/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2013 OpenFOAM Foundation
    Copyright (C) 2020-2023 OpenCFD Ltd.
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

#include "fields/DimensionedFields/DimensionedTensorField/DimensionedTensorField.H"
#include "fields/Fields/tensorField/tensorField.H"

#define TEMPLATE template<class GeoMesh>
#include "fields/DimensionedFields/DimensionedField/DimensionedFieldFunctionsM.C"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

UNARY_FUNCTION(scalar, tensor, tr, transform)
UNARY_FUNCTION(sphericalTensor, tensor, sph, transform)
UNARY_FUNCTION(symmTensor, tensor, symm, transform)
UNARY_FUNCTION(symmTensor, tensor, twoSymm, transform)
UNARY_FUNCTION(symmTensor, tensor, devSymm, transform)
UNARY_FUNCTION(symmTensor, tensor, devTwoSymm, transform)
UNARY_FUNCTION(tensor, tensor, skew, transform)
UNARY_FUNCTION(tensor, tensor, dev, transform)
UNARY_FUNCTION(tensor, tensor, dev2, transform)
UNARY_FUNCTION(scalar, tensor, det, pow3)
UNARY_FUNCTION(tensor, tensor, cof, pow2)
UNARY_FUNCTION(tensor, tensor, inv, inv)

UNARY_FUNCTION(vector, symmTensor, eigenValues, transform)
UNARY_FUNCTION(tensor, symmTensor, eigenVectors, sign)


// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

UNARY_OPERATOR(vector, tensor, *, hdual, transform)
UNARY_OPERATOR(tensor, vector, *, hdual, transform)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "fields/Fields/Field/undefFieldFunctionsM.H"

// ************************************************************************* //
