/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
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

#include "matrices/LduMatrixCaseDir/Preconditioners/NoPreconditioner/NoPreconditionerPascal.H"
#include "matrices/LduMatrixCaseDir/Preconditioners/DiagonalPreconditioner/DiagonalPreconditionerPascal.H"
#include "matrices/LduMatrixCaseDir/Preconditioners/DILUPreconditioner/TDILUPreconditioner.H"
#include "fields/Fields/fieldTypes.H"

#define makeLduPreconditioners(Type, DType, LUType)                            \
                                                                               \
    makeLduPreconditioner(NoPreconditioner, Type, DType, LUType);              \
    makeLduSymPreconditioner(NoPreconditioner, Type, DType, LUType);           \
    makeLduAsymPreconditioner(NoPreconditioner, Type, DType, LUType);          \
                                                                               \
    makeLduPreconditioner(DiagonalPreconditioner, Type, DType, LUType);        \
    makeLduSymPreconditioner(DiagonalPreconditioner, Type, DType, LUType);     \
    makeLduAsymPreconditioner(DiagonalPreconditioner, Type, DType, LUType);    \
                                                                               \
    makeLduPreconditioner(TDILUPreconditioner, Type, DType, LUType);           \
    makeLduAsymPreconditioner(TDILUPreconditioner, Type, DType, LUType);

namespace Foam
{
    makeLduPreconditioners(scalar, scalar, scalar);
    makeLduPreconditioners(vector, scalar, scalar);
    makeLduPreconditioners(sphericalTensor, scalar, scalar);
    makeLduPreconditioners(symmTensor, scalar, scalar);
    makeLduPreconditioners(tensor, scalar, scalar);
};


// ************************************************************************* //
