/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2014-2015 OpenFOAM Foundation
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
    Foam::turbulentDispersionModels::Gosman

Description
    Turbulent dispersion model of Gosman et al.

    Reference:
    \verbatim
        "Multidimensional modeling of turbulent two-phase flows in stirred
         vessels"
        Gosman, A.D., Lekakou, C., Politis, S., Issa, R.I., and Looney, M.K.,
        AIChE Journal
        Volume 38, Issue 12, 1992, pp. 1946-1956
     \endverbatim

SourceFiles
    Gosman.C

\*---------------------------------------------------------------------------*/

#ifndef Gosman_H
#define Gosman_H

#include "interfacialModels/turbulentDispersionModels/turbulentDispersionModel/turbulentDispersionModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class phasePair;

namespace turbulentDispersionModels
{

/*---------------------------------------------------------------------------*\
                             Class Gosman Declaration
\*---------------------------------------------------------------------------*/

class Gosman
:
    public turbulentDispersionModel
{
    // Private data

        //- Schmidt number
        const dimensionedScalar sigma_;


public:

    //- Runtime type information
    TypeName("Gosman");


    // Constructors

        //- Construct from a dictionary and a phase pair
        Gosman
        (
            const dictionary& dict,
            const phasePair& pair
        );


    //- Destructor
    virtual ~Gosman();


    // Member Functions

        //- Turbulent diffusivity
        //  multiplying the gradient of the phase-fraction
        virtual tmp<volScalarField> D() const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbulentDispersionModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
