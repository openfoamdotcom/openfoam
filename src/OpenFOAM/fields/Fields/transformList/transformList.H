/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2018 OpenCFD Ltd.
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

InClass
    Foam

Description
    Spatial transformation functions for list of values and primitive fields.

SourceFiles
    transformList.C

\*---------------------------------------------------------------------------*/

#ifndef Foam_transformList_H
#define Foam_transformList_H

#include "primitives/transform/transform.H"
#include "containers/Lists/List/List.H"
#include "containers/HashTables/Map/Map.H"
#include "meshes/meshShapes/edge/edgeHashes.H"
#include "fields/Fields/tensorField/tensorField.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//- Apply transform to a list of elements, returning a copy.
template<class T>
List<T> transform(const tensor& rotTensor, const UList<T>& field);

//- Inplace transform a list of elements.
template<class T>
void transformList(const tensor& rotTensor, UList<T>& field);

//- Inplace transform a list of elements using one tensor per element.
template<class T>
void transformList(const tensorField& rotTensor, UList<T>& field);

//- Inplace transform a Map of elements.
template<class T>
void transformList(const tensor& rotTensor, Map<T>& field);

//- Inplace transform a Map of elements.
//  Using multiple tensors is ill-defined (Fatal).
template<class T>
void transformList(const tensorField& rotTensor, Map<T>& field);

//- Inplace transform a Map of elements.
//  Using multiple tensors is ill-defined (Fatal).
template<class T>
void transformList(const tensor& rotTensor, EdgeMap<T>& field);

//- Inplace transform a Map of elements.
//  Using multiple tensors is ill-defined (Fatal).
template<class T>
void transformList(const tensorField& rotTensor, EdgeMap<T>& field);


// Specialisations for bool (no-op)
template<> inline void transformList(const tensor&, UList<bool>&) {}
template<> inline void transformList(const tensorField&, UList<bool>&) {}
template<> inline void transformList(const tensor&, Map<bool>&) {}
template<> inline void transformList(const tensorField&, Map<bool>&) {}
template<> inline void transformList(const tensor&, EdgeMap<bool>&) {}
template<> inline void transformList(const tensorField&, EdgeMap<bool>&) {}


// Specialisations for label (no-op)
template<> inline void transformList(const tensor&, labelUList&) {}
template<> inline void transformList(const tensorField&, labelUList&) {}
template<> inline void transformList(const tensor&, Map<label>&) {}
template<> inline void transformList(const tensorField&, Map<label>&) {}
template<> inline void transformList(const tensor&, EdgeMap<label>&) {}
template<> inline void transformList(const tensorField&, EdgeMap<label>&) {}


// Specialisations for scalar (no-op)
template<> inline void transformList(const tensor&, UList<scalar>&) {}
template<> inline void transformList(const tensorField&, UList<scalar>&) {}
template<> inline void transformList(const tensor&, Map<scalar>&) {}
template<> inline void transformList(const tensorField&, Map<scalar>&) {}
template<> inline void transformList(const tensor&, EdgeMap<scalar>&) {}
template<> inline void transformList(const tensorField&, EdgeMap<scalar>&) {}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "fields/Fields/transformList/transformList.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
