/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2021 OpenCFD Ltd
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
    Foam::wallBoilingModels::nucleateFluxModel

Description
    Base class for nucleation flux models

SourceFiles
    nucleateFluxModel.C

\*---------------------------------------------------------------------------*/

#ifndef nucleateFluxModel_H
#define nucleateFluxModel_H

#include "fields/volFields/volFields.H"
#include "db/dictionary/dictionary.H"
#include "db/runTimeSelection/construction/runTimeSelectionTables.H"
#include "phaseModel/phaseModel/reactingEuler_phaseModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace wallBoilingModels
{
/*---------------------------------------------------------------------------*\
                         Class nucleateFluxModel Declaration
\*---------------------------------------------------------------------------*/

class nucleateFluxModel
{
public:

    //- Runtime type information
    TypeName("nucleateFluxModel");


    //- Declare runtime construction
    declareRunTimeSelectionTable
    (
        autoPtr,
        nucleateFluxModel,
        dictionary,
        (
            const dictionary& dict
        ),
        (dict)
    );


    // Generated Methods

        //- Default construct
        nucleateFluxModel() = default;

        //- Destructor
        virtual ~nucleateFluxModel() = default;


    // Selectors

        //- Select default constructed
        static autoPtr<nucleateFluxModel> New(const dictionary& dict);


    // Member Functions

        //- Calculate nucleate heat flux
        virtual tmp<scalarField> qNucleate
        (
            const phaseModel& liquid,
            const phaseModel& vapor,
            const label patchi,
            const scalarField& Tl,
            const scalarField& Tsatw,
            const scalarField& L
        ) const = 0;

        //- Write
        virtual void write(Ostream& os) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace wallBoilingModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
