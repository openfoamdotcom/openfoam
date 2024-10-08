/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2012 OpenFOAM Foundation
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
    Foam::XiGModels::instabilityG

Description
    Flame-surface instabilityG flame-wrinkling generation rate coefficient model
    used in \link XiModel.H \endlink.

    See Technical Report SH/RE/01R for details on the PDR modelling.

SourceFiles
    instabilityG.C

\*---------------------------------------------------------------------------*/

#ifndef instabilityG_H
#define instabilityG_H

#include "XiModels/XiGModels/XiGModel/XiGModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace XiGModels
{

/*---------------------------------------------------------------------------*\
                          Class instabilityG Declaration
\*---------------------------------------------------------------------------*/

class instabilityG
:
    public XiGModel
{
    // Private data

        //- Flame instabilityG wrinkling generation rate coefficient
        dimensionedScalar GIn_;

        //- InstabilityG length-scale
        dimensionedScalar lambdaIn_;

        //- Xi generation rate model due to all other processes
        autoPtr<XiGModel> XiGModel_;


    // Private Member Functions

        //- No copy construct
        instabilityG(const instabilityG&) = delete;

        //- No copy assignment
        void operator=(const instabilityG&) = delete;


public:

    //- Runtime type information
    TypeName("instabilityG");


    // Constructors

        //- Construct from components
        instabilityG
        (
            const dictionary& XiGProperties,
            const psiuReactionThermo& thermo,
            const compressible::RASModel& turbulence,
            const volScalarField& Su
        );


    //- Destructor
    virtual ~instabilityG();


    // Member Functions

        //- Return the flame-wrinkling generation rate
        virtual tmp<volScalarField> G() const;

        //- Return the flame diffusivity
        virtual tmp<volScalarField> Db() const;

        //- Update properties from given dictionary
        virtual bool read(const dictionary& XiGProperties);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace XiGModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
