/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2015 OpenFOAM Foundation
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
    Foam::heatTransferModels::sphericalHeatTransfer

Description
    Model which applies an analytical solution for heat transfer from the
    surface of a sphere to the fluid within the sphere.

SourceFiles
    sphericalHeatTransfer.C

\*---------------------------------------------------------------------------*/

#ifndef sphericalHeatTransfer_H
#define sphericalHeatTransfer_H

#include "interfacialModels/heatTransferModels/heatTransferModel/heatTransferModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class phasePair;

namespace heatTransferModels
{

/*---------------------------------------------------------------------------*\
                          Class sphericalHeatTransfer Declaration
\*---------------------------------------------------------------------------*/

class sphericalHeatTransfer
:
    public heatTransferModel
{
public:

    //- Runtime type information
    TypeName("spherical");


    // Constructors

        //- Construct from components
        sphericalHeatTransfer
        (
            const dictionary& dict,
            const phasePair& pair
        );


    //- Destructor
    virtual ~sphericalHeatTransfer();


    // Member Functions

        //- The heat transfer function K used in the enthalpy equation
        tmp<volScalarField> K() const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace heatTransferModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
