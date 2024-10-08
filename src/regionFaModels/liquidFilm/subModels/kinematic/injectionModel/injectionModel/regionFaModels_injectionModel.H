/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2021 OpenCFD Ltd.
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
    Foam::regionModels::areaSurfaceFilmModels::injectionModel

Description
    Base class for film injection models, handling mass transfer from the
    film.

SourceFiles
    injectionModel.C
    injectionModelNew.C

\*---------------------------------------------------------------------------*/

#ifndef regionFaModels_injectionModel_H
#define regionFaModels_injectionModel_H

#include "liquidFilm/subModels/regionFaModels_filmSubModelBase.H"
#include "db/runTimeSelection/construction/runTimeSelectionTables.H"
#include "fields/Fields/scalarField/scalarField.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace regionModels
{
namespace areaSurfaceFilmModels
{

/*---------------------------------------------------------------------------*\
                      Class injectionModel Declaration
\*---------------------------------------------------------------------------*/

class injectionModel
:
    public filmSubModelBase
{
    // Private Data

        //- Injected mass
        scalar injectedMass_;


    // Private Member Functions

        //- No copy construct
        injectionModel(const injectionModel&) = delete;

        //- No copy assignment
        void operator=(const injectionModel&) = delete;


protected:

    // Protected Member Functions

        //- Add to injected mass
        void addToInjectedMass(const scalar dMass);

        //- Correct
        void correct();


public:

    //- Runtime type information
    TypeName("injectionModel");


    // Declare runtime constructor selection table

         declareRunTimeSelectionTable
         (
             autoPtr,
             injectionModel,
             dictionary,
             (
                liquidFilmBase& film,
                const dictionary& dict
             ),
             (film, dict)
         );


    // Constructors

        //- Construct null
        injectionModel(liquidFilmBase& film);

        //- Construct from type name, dictionary and surface film model
        injectionModel
        (
            const word& modelType,
            liquidFilmBase& film,
            const dictionary& dict
        );


    // Selectors

        //- Return a reference to the selected injection model
        static autoPtr<injectionModel> New
        (
            liquidFilmBase& film,
            const dictionary& dict,
            const word& mdoelType
        );


    //- Destructor
    virtual ~injectionModel();


    // Member Functions

        //- Correct
        virtual void correct
        (
            scalarField& availableMass,
            scalarField& massToInject,
            scalarField& diameterToInject
        ) = 0;

        //- Return the total mass injected
        virtual scalar injectedMassTotal() const;

        //- Accumulate the total mass injected for the patches into the
        //- scalarField provided
        virtual void patchInjectedMassTotals(scalar& patchMasses) const
        {}
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace areaSurfaceFilmModels
} // End namespace regionModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
