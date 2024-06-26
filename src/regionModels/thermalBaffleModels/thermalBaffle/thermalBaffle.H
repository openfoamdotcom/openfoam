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

Class
    Foam::regionModels::thermalBaffleModels::thermalBaffle

Description
    2D thermal baffle

SourceFiles
    thermalBaffle.C
    thermalBaffleI.H

\*---------------------------------------------------------------------------*/

#ifndef thermalBaffle_H
#define thermalBaffle_H

#include "thermalBaffleModel/thermalBaffleModel.H"
#include "fields/volFields/volFieldsFwd.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace regionModels
{
namespace thermalBaffleModels
{


/*---------------------------------------------------------------------------*\
                        Class thermalBaffle Declaration
\*---------------------------------------------------------------------------*/

class thermalBaffle
:
    public thermalBaffleModel
{
private:

    // Private member functions

        //- No copy construct
        thermalBaffle(const thermalBaffle&) = delete;

        //- No copy assignment
        void operator=(const thermalBaffle&) = delete;

        //- Initialize thermalBaffle
        void init();


protected:

    // Protected data

        // Solution parameters

            //- Number of non orthogonal correctors
            label nNonOrthCorr_;


        // Thermo properties

            //- Solid thermo
            autoPtr<solidThermo> thermo_;

            //- Enthalpy/internal energy
            volScalarField& h_;


        // Source term fields

            //- Surface energy source  / [J/m2/s]
            volScalarField qs_;

            //- Volumetric energy source  / [J/m3/s]
            volScalarField Q_;


        // Sub models

            //- Pointer to radiation model
            autoPtr<radiation::radiationModel> radiation_;


    // Protected member functions

        //- Read control parameters IO dictionary
        virtual bool read();

        //- Read control parameters from dictionary
        virtual bool read(const dictionary& dict);


        // Equations

            //- Solve energy equation
            void solveEnergy();


public:

    //- Runtime type information
    TypeName("thermalBaffle");


    // Constructors

        //- Construct from components
        thermalBaffle(const word& modelType, const fvMesh& mesh);

        //- Construct from components and dict
        thermalBaffle
        (
            const word& modelType,
            const fvMesh& mesh,
            const dictionary& dict
        );


    //- Destructor
    virtual ~thermalBaffle();


    // Member Functions

        // Thermo properties

            //- Return const reference to the solidThermo
            virtual const solidThermo& thermo() const;


            // Fields

                //- Return the film specific heat capacity [J/kg/K]
                virtual const tmp<volScalarField> Cp() const;

                //- Return solid absortivity [1/m]
                virtual const volScalarField& kappaRad() const;

                //- Return temperature [K]
                virtual const volScalarField& T() const;

                //- Return density [Kg/m3]
                virtual const volScalarField& rho() const;

                //- Return thermal conductivity [W/m/K]
                virtual const volScalarField& kappa() const;


            // Helper functions

                //- Return sensible enthalpy/internal energy
                //  as a function of temperature
                //  for a patch
                inline tmp<scalarField> he
                (
                    const scalarField& p,
                    const scalarField& T,
                    const label patchi
                ) const;

                //- Return sensible enthalpy/internal energy
                inline tmp<volScalarField> he() const;


        // Evolution

            //- Pre-evolve  thermal baffle
            virtual void preEvolveRegion();

            //- Evolve the thermal baffle
            virtual void evolveRegion();


       // I-O

            //- Provide some feedback
            virtual void info();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace thermalBaffleModels
} // End namespace regionModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "thermalBaffle/thermalBaffleI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
