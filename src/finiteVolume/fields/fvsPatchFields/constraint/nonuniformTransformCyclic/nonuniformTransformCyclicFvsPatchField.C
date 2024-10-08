/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2015 OpenFOAM Foundation
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

#include "fields/fvsPatchFields/constraint/nonuniformTransformCyclic/nonuniformTransformCyclicFvsPatchField.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
Foam::nonuniformTransformCyclicFvsPatchField<Type>::
nonuniformTransformCyclicFvsPatchField
(
    const fvPatch& p,
    const DimensionedField<Type, surfaceMesh>& iF
)
:
    cyclicFvsPatchField<Type>(p, iF)
{}


template<class Type>
Foam::nonuniformTransformCyclicFvsPatchField<Type>::
nonuniformTransformCyclicFvsPatchField
(
    const fvPatch& p,
    const DimensionedField<Type, surfaceMesh>& iF,
    const dictionary& dict
)
:
    cyclicFvsPatchField<Type>(p, iF, dict)
{}


template<class Type>
Foam::nonuniformTransformCyclicFvsPatchField<Type>::
nonuniformTransformCyclicFvsPatchField
(
    const nonuniformTransformCyclicFvsPatchField<Type>& ptf,
    const fvPatch& p,
    const DimensionedField<Type, surfaceMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    cyclicFvsPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
Foam::nonuniformTransformCyclicFvsPatchField<Type>::
nonuniformTransformCyclicFvsPatchField
(
    const nonuniformTransformCyclicFvsPatchField<Type>& ptf
)
:
    cyclicFvsPatchField<Type>(ptf)
{}


template<class Type>
Foam::nonuniformTransformCyclicFvsPatchField<Type>::
nonuniformTransformCyclicFvsPatchField
(
    const nonuniformTransformCyclicFvsPatchField<Type>& ptf,
    const DimensionedField<Type, surfaceMesh>& iF
)
:
    cyclicFvsPatchField<Type>(ptf, iF)
{}


// ************************************************************************* //
