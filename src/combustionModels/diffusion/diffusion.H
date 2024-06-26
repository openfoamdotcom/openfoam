/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2012-2017 OpenFOAM Foundation
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
    Foam::combustionModels::diffusion

Group
    grpCombustionModels

Description
    Simple diffusion-based combustion model based on the principle mixed is
    burnt. Additional parameter C is used to distribute the heat release rate
    in time.

SourceFiles
    diffusion.C

\*---------------------------------------------------------------------------*/

#ifndef diffusion_H
#define diffusion_H

#include "singleStepCombustion/singleStepCombustion.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace combustionModels
{

/*---------------------------------------------------------------------------*\
                         Class diffusion Declaration
\*---------------------------------------------------------------------------*/

template<class ReactionThermo, class ThermoType>
class diffusion
:
    public singleStepCombustion<ReactionThermo, ThermoType>
{
    // Private data

        //- Model constant
        scalar C_;

        //- Name of oxidant - default is "O2"
        word oxidantName_;


    // Private Member Functions

        //- No copy construct
        diffusion(const diffusion&) = delete;

        //- No copy assignment
        void operator=(const diffusion&) = delete;


public:

    //- Runtime type information
    TypeName("diffusion");


    // Constructors

        //- Construct from components
        diffusion
        (
            const word& modelType,
            ReactionThermo& thermo,
            const compressibleTurbulenceModel& turb,
            const word& combustionProperties
        );


    //- Destructor
    virtual ~diffusion();


    // Member Functions

        //- Correct combustion rate
        virtual void correct();

        //- Update properties
        virtual bool read();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace combustionModels
} // End namespace Foam


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "diffusion/diffusion.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
