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

Global
    dimensionSets

Description
    Useful dimension sets

SourceFiles
    dimensionSets.C

\*---------------------------------------------------------------------------*/

#ifndef Foam_dimensionSets_H
#define Foam_dimensionSets_H

#include "matrices/scalarMatrices/scalarMatrices.H"
#include "dimensionedTypes/dimensionedScalar/dimensionedScalarFwd.H"
#include "containers/PtrLists/PtrList/PtrList.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//- Dimensionless
extern const dimensionSet dimless;

extern const dimensionSet dimMass;
extern const dimensionSet dimLength;
extern const dimensionSet dimTime;
extern const dimensionSet dimTemperature;
extern const dimensionSet dimMoles;
extern const dimensionSet dimCurrent;
extern const dimensionSet dimLuminousIntensity;

extern const dimensionSet dimArea;
extern const dimensionSet dimVolume;

//- Older spelling for dimVolume
//  \deprecated(2019-01) use dimVolume instead
extern const dimensionSet dimVol;

extern const dimensionSet dimDensity;
extern const dimensionSet dimForce;
extern const dimensionSet dimEnergy;
extern const dimensionSet dimPower;

extern const dimensionSet dimVelocity;
extern const dimensionSet dimAcceleration;
extern const dimensionSet dimPressure;
extern const dimensionSet dimCompressibility;
extern const dimensionSet dimGasConstant;
extern const dimensionSet dimSpecificHeatCapacity;
extern const dimensionSet dimViscosity;
extern const dimensionSet dimDynamicViscosity;


/*---------------------------------------------------------------------------*\
                        Class dimensionSets Declaration
\*---------------------------------------------------------------------------*/

//- Construction of unit sets
class dimensionSets
{
    // Private Data

        //- Set of dimensions
        PtrList<dimensionedScalar> units_;

        //- LU decomposition of dimensions
        scalarSquareMatrix conversion_;

        //- See above
        labelList conversionPivots_;

        //- Is LU decomposition valid
        bool valid_;

public:

    // Constructors

        //- Construct from all units and set of units to use
        //- for inversion (writing)
        dimensionSets
        (
            const HashTable<dimensionedScalar>&,
            const wordList& unitNames
        );


    // Member Functions

        //- Return the units
        const PtrList<dimensionedScalar>& units() const noexcept
        {
            return units_;
        }

        //- Is there a valid inverse of the selected unit
        bool good() const noexcept { return valid_; }

        //- Is there a valid inverse of the selected unit
        bool valid() const noexcept { return valid_; }

        //- (if valid) obtain set of coefficients of unitNames
        void coefficients(scalarField& exponents) const;
};


//- Top level dictionary
dictionary& dimensionSystems();

//- Set of all dimensions
const HashTable<dimensionedScalar>& unitSet();

//- Set of units
const dimensionSets& writeUnitSet();


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
