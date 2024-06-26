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
    Foam::regionModels::pyrolysisModels::noPyrolysis

Description
    Dummy surface pyrolysis model for 'none'

SourceFiles
    noPyrolysis.C

\*---------------------------------------------------------------------------*/

#ifndef noPyrolysis_H
#define noPyrolysis_H

#include "pyrolysisModel/pyrolysisModel.H"
#include "fields/volFields/volFieldsFwd.H"
#include "basicSolidChemistryModel/basicSolidChemistryModel.H"
#include "radiationModels/radiationModel/radiationModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace regionModels
{
namespace pyrolysisModels
{

/*---------------------------------------------------------------------------*\
                         Class noPyrolysis Declaration
\*---------------------------------------------------------------------------*/

class noPyrolysis
:
    public pyrolysisModel
{
private:

    // Private member functions

        //- No copy construct
        noPyrolysis(const noPyrolysis&) = delete;

        //- No copy assignment
        void operator=(const noPyrolysis&) = delete;


protected:

    // Protected member functions

        //- Read control parameters from dictionary
        virtual bool read();

        //- Read control parameters from dictionary
        virtual bool read(const dictionary& dict);

        //- Reset solidChemistryModel and solidThermo pointers
        void constructThermoChemistry();

        //- Reference to solid thermo
        autoPtr<solidReactionThermo> solidThermo_;

        //- Reference to the solid chemistry model
        autoPtr<basicSolidChemistryModel> solidChemistry_;

         //- Pointer to radiation model
        autoPtr<radiation::radiationModel> radiation_;


public:

    //- Runtime type information
    TypeName("none");


    // Constructors

        //- Construct from type name and mesh
        noPyrolysis
        (
            const word& modelType,
            const fvMesh& mesh,
            const word& regionType
        );

        //- Construct from type name and mesh and dict
        noPyrolysis
        (
            const word& modelType,
            const fvMesh& mesh,
            const dictionary& dict,
            const word& regionType
        );


    //- Destructor
    virtual ~noPyrolysis();


    // Member Functions

        // Fields

            //- Return density [kg/m3]
            virtual const volScalarField& rho() const;

            //- Return const temperature [K]
            virtual const volScalarField& T() const;

            //- Return specific heat capacity [J/kg/K]
            virtual const tmp<volScalarField> Cp() const;

            //- Return the region absorptivity [1/m]
            virtual tmp<volScalarField> kappaRad() const;

            //- Return the region thermal conductivity [W/m/k]
            virtual tmp<volScalarField> kappa() const;

            //- Return the total gas mass flux to primary region [kg/m2/s]
            virtual const surfaceScalarField& phiGas() const;


        // Evolution

            //- Pre-evolve region
            virtual void preEvolveRegion();

            //- Evolve the pyrolysis equations
            virtual void evolveRegion();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace pyrolysisModels
} // End namespace regionModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
