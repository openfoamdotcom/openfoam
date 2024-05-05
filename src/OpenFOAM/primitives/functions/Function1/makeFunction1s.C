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

#include "primitives/functions/Function1/Coded/CodedFunction1.H"
#include "primitives/functions/Function1/Constant/Constant.H"
#include "primitives/functions/Function1/Uniform/UniformPascal.H"
#include "primitives/functions/Function1/Zero/ZeroConstant.H"
#include "primitives/functions/Function1/One/OneConstant.H"
#include "primitives/functions/Function1/None/NoneFunction1.H"
#include "primitives/functions/Function1/Polynomial/PolynomialEntry.H"
#include "primitives/functions/Function1/Sine/Sine.H"
#include "primitives/functions/Function1/Cosine/CosinePascal.H"
#include "primitives/functions/Function1/Square/Square.H"
#include "primitives/functions/Function1/CSV/CSV.H"
#include "primitives/functions/Function1/Table/Table.H"
#include "primitives/functions/Function1/TableFile/TableFile.H"
#include "primitives/functions/Function1/Scale/Scale.H"
#include "primitives/functions/Function1/InputValueMapper/InputValueMapper.H"
#include "primitives/functions/Function1/FunctionObjectTrigger/FunctionObjectTrigger.H"
#include "primitives/functions/Function1/FunctionObjectValue/FunctionObjectValue.H"
#include "fields/Fields/fieldTypes.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeFunction1s(Type)                                                   \
    makeFunction1(Type);                                                       \
    makeFunction1Type(CodedFunction1, Type);                                   \
    makeFunction1Type(Constant, Type);                                         \
    makeFunction1Type(Uniform, Type);                                          \
    makeFunction1Type(None, Type);                                             \
    makeFunction1Type(ZeroConstant, Type);                                     \
    makeFunction1Type(OneConstant, Type);                                      \
    makeFunction1Type(Polynomial, Type);                                       \
    makeFunction1Type(Cosine, Type);                                           \
    makeFunction1Type(Sine, Type);                                             \
    makeFunction1Type(Square, Type);                                           \
    makeFunction1Type(CSV, Type);                                              \
    makeFunction1Type(Table, Type);                                            \
    makeFunction1Type(TableFile, Type);                                        \
    makeFunction1Type(Scale, Type);                                            \
    makeFunction1Type(InputValueMapper, Type);                                 \
    makeFunction1Type(FunctionObjectValue, Type);

#define makeFieldFunction1s(Type)                                              \
    makeFunction1(Type);                                                       \
    makeFunction1Type(Constant, Type);                                         \
    makeFunction1Type(Uniform, Type);                                          \
    makeFunction1Type(Table, Type);                                            \
    makeFunction1Type(TableFile, Type);                                        \

namespace Foam
{
    makeFunction1(label);
    makeFunction1Type(Constant, label);
    makeFunction1Type(None, label);

    makeFunction1Type(FunctionObjectTrigger, label);
    makeFunction1Type(FunctionObjectTrigger, scalar);
    // Only (label/scalar) makes sense for triggers

    makeFunction1s(scalar);
    makeFunction1s(vector);
    makeFunction1s(sphericalTensor);
    makeFunction1s(symmTensor);
    makeFunction1s(tensor);

    makeFieldFunction1s(scalarField);
}


// ************************************************************************* //
