/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
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
    Foam::regionModels::surfaceFilmModels::noFilm

Description
    Dummy surfaceFilmModel to allow solvers supporting film simulations to be
    run without a film region.

SourceFiles
    noFilm.C

\*---------------------------------------------------------------------------*/

#ifndef noFilm_H
#define noFilm_H

#include "surfaceFilmModel/surfaceFilmModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace regionModels
{
namespace surfaceFilmModels
{

/*---------------------------------------------------------------------------*\
                          Class noFilm Declaration
\*---------------------------------------------------------------------------*/

class noFilm
:
    public surfaceFilmModel
{
    // Private member data

        //- Reference to the mesh
        const fvMesh& mesh_;


    // Private member functions

        //- No copy construct
        noFilm(const noFilm&) = delete;

        //- No copy assignment
        void operator=(const noFilm&) = delete;


public:

    //- Runtime type information
    TypeName("none");


    // Constructors

        //- Construct from components
        noFilm
        (
            const word& modelType,
            const fvMesh& mesh,
            const dimensionedVector& g,
            const word& regionType
        );


    //- Destructor
    virtual ~noFilm();


    // Member Functions

        // Solution parameters

            //- Courant number evaluation
            virtual scalar CourantNumber() const;


        // Primary region source fields

            //- Return total mass source - Eulerian phase only
            virtual tmp<volScalarField::Internal> Srho() const;

            //- Return mass source for specie i - Eulerian phase only
            virtual tmp<volScalarField::Internal> Srho
            (
                const label i
            ) const;

            //- Return enthalpy source - Eulerian phase only
            virtual tmp<volScalarField::Internal> Sh() const;


        // Evolution

            //- Main driver routing to evolve the region - calls other evolves
            virtual void evolve();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace surfaceFilmModels
} // regionModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
