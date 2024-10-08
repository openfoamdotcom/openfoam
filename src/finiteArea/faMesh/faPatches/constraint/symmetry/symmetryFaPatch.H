/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016-2017 Wikki Ltd
    Copyright (C) 2019-2022 OpenCFD Ltd.
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
    Foam::symmetryFaPatch

Description
    Symmetry-plane patch.

Author
    Zeljko Tukovic, FMENA
    Hrvoje Jasak, Wikki Ltd.

SourceFiles
    symmetryFaPatch.C

\*---------------------------------------------------------------------------*/

#ifndef Foam_symmetryFaPatch_H
#define Foam_symmetryFaPatch_H

#include "faMesh/faPatches/faPatch/faPatch.H"
#include "meshes/polyMesh/polyPatches/constraint/symmetry/symmetryPolyPatch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                       Class symmetryFaPatch Declaration
\*---------------------------------------------------------------------------*/

class symmetryFaPatch
:
    public faPatch
{
protected:

    // Protected Member Functions

        //- Make patch face non-orthogonality correction vectors
        virtual void makeCorrVecs(vectorField&) const;


public:

    //- Runtime type information
    TypeName(symmetryPolyPatch::typeName_());  // ie, "symmetry"


    // Constructors

        //- Construct from components
        symmetryFaPatch
        (
            const word& name,
            const labelUList& edgeLabels,
            const label index,
            const faBoundaryMesh& bm,
            const label nbrPolyPatchi,
            const word& patchType
        );

        //- Construct from dictionary
        symmetryFaPatch
        (
            const word& name,
            const dictionary& dict,
            const label index,
            const faBoundaryMesh& bm,
            const word& patchType
        );

        //- Copy construct, resetting boundary mesh
        symmetryFaPatch(const symmetryFaPatch& p, const faBoundaryMesh& bm);

        //- Copy construct, resetting boundary mesh and addressing
        symmetryFaPatch
        (
            const symmetryFaPatch& p,
            const faBoundaryMesh& bm,
            const label index,
            const labelUList& edgeLabels,
            const label nbrPolyPatchi
        );


        //- Construct and return a clone, resetting the boundary mesh
        virtual autoPtr<faPatch> clone(const faBoundaryMesh& bm) const
        {
            return autoPtr<faPatch>
            (
                new symmetryFaPatch(*this, bm)
            );
        }

        //- Construct and return a clone, resetting the edge list
        //- and boundary mesh
        virtual autoPtr<faPatch> clone
        (
            const faBoundaryMesh& bm,
            const labelUList& edgeLabels,
            const label index,
            const label nbrPolyPatchi
        ) const
        {
            return autoPtr<faPatch>
            (
                new symmetryFaPatch
                (
                    *this,
                    bm,
                    index,
                    edgeLabels,
                    nbrPolyPatchi
                )
            );
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
