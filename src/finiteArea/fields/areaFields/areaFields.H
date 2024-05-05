/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016-2017 Wikki Ltd
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
    Foam::areaFields

Description
    Finite area area (element) fields

Author
    Zeljko Tukovic, FMENA
    Hrvoje Jasak, Wikki Ltd.

SourceFiles
    areaFields.C

\*---------------------------------------------------------------------------*/

#ifndef Foam_areaFields_H
#define Foam_areaFields_H

#include "db/objectRegistry/objectRegistry.H"
#include "fields/GeometricFields/GeometricField/GeometricFields.H"
#include "areaMesh/areaFaMesh.H"
#include "faMesh/faMesh.H"
#include "fields/faPatchFields/faPatchField/faPatchFields.H"
#include "fields/areaFields/areaFieldsFwd.H"
#include "fields/faPatchFields/basic/calculated/calculatedFaPatchFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Specializations

template<>
tmp<GeometricField<scalar, faPatchField, areaMesh>>
GeometricField<scalar, faPatchField, areaMesh>::component
(
    const direction
) const;

template<>
void GeometricField<scalar, faPatchField, areaMesh>::replace
(
    const direction,
    const GeometricField<scalar, faPatchField, areaMesh>& sf
);

template<>
bool GeometricBoundaryField<scalar, faPatchField, areaMesh>::check() const;
template<>
bool GeometricBoundaryField<vector, faPatchField, areaMesh>::check() const;
template<>
bool GeometricBoundaryField<sphericalTensor, faPatchField, areaMesh>::check
() const;
template<>
bool GeometricBoundaryField<symmTensor, faPatchField, areaMesh>::check() const;
template<>
bool GeometricBoundaryField<tensor, faPatchField, areaMesh>::check() const;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
