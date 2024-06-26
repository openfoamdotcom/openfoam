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

Class
    Foam::reactionRateFlameAreaModels::relaxation

Description
    Consumption rate per unit of flame area obtained from a relaxation equation

SourceFiles
    relaxation.C

\*---------------------------------------------------------------------------*/

#ifndef relaxation_H
#define relaxation_H

#include "FSD/reactionRateFlameAreaModels/reactionRateFlameArea/reactionRateFlameArea.H"
#include "FSD/reactionRateFlameAreaModels/consumptionSpeed/consumptionSpeed.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace reactionRateFlameAreaModels
{

/*---------------------------------------------------------------------------*\
                           Class relaxation Declaration
\*---------------------------------------------------------------------------*/

class relaxation
:
    public reactionRateFlameArea
{
    // Private Data

        //- Correlation
        consumptionSpeed correlation_;

        //- Proportionality constant for time scale in the relaxation Eq.
        scalar C_;

        //- Proportionality constant for sub-grid strain
        scalar alpha_;


     // Private Member Functions

        //- No copy construct
        relaxation(const relaxation&) = delete;

        //- No copy assignment
        void operator=(const relaxation&) = delete;


public:

    //- Runtime type information
    TypeName("relaxation");


    // Constructors

        //- Construct from dictionary and psiReactionThermo
        relaxation
        (
            const word modelType,
            const dictionary& dictCoeffs,
            const fvMesh& mesh,
            const combustionModel& combModel
        );


    // Destructor

        virtual ~relaxation();


    // Member functions

        //- Correct omega
        virtual void correct(const volScalarField& sigma);


    // IO

        //- Update properties from given dictionary
        virtual bool read(const dictionary& dictProperties);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End reactionRateFlameAreaModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
