/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
    Copyright (C) 2020 OpenCFD Ltd.
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
    Foam::specie

Description
    Base class of the thermophysical property types.

SourceFiles
    specieI.H
    specie.C

\*---------------------------------------------------------------------------*/

#ifndef specie_H
#define specie_H

#include "primitives/strings/word/word.H"
#include "primitives/Scalar/scalar/scalar.H"
#include "db/dictionary/dictionary.H"

#include "global/constants/thermodynamic/thermodynamicConstants.H"
using namespace Foam::constant::thermodynamic;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward Declarations
class specie;

inline specie operator+(const specie&, const specie&);
inline specie operator*(const scalar, const specie&);
inline specie operator==(const specie&, const specie&);

Ostream& operator<<(Ostream&, const specie&);


/*---------------------------------------------------------------------------*\
                           Class specie Declaration
\*---------------------------------------------------------------------------*/

class specie
{
    // Private Data

        //- Name of specie
        word name_;

        //- Number of moles of this component in the mixture
        scalar Y_;

        //- Molecular weight of specie [kg/kmol]
        scalar molWeight_;


public:

    //- Declare type-name (with debug switch)
    ClassName("specie");


    // Generated Methods

        //- Copy construct
        specie(const specie&) = default;


    // Constructors

        //- Construct from components without name
        inline specie(const scalar Y, const scalar molWeight);

        //- Construct from components with name
        inline specie
        (
            const word& name,
            const scalar Y,
            const scalar molWeight
        );

        //- Construct as named copy
        inline specie(const word& name, const specie&);

        //- Construct from dictionary
        explicit specie(const dictionary& dict);


    // Member Functions

        // Access

            //- Name
            inline const word& name() const;

            //- Molecular weight [kg/kmol]
            inline scalar W() const;

            //- No of moles of this species in mixture
            inline scalar Y() const;

            //- Gas constant [J/(kg K)]
            inline scalar R() const;


        // IO

            //- Write to Ostream
            void write(Ostream& os) const;


    // Member Operators

        //- Copy assignment, preserve original name
        inline void operator=(const specie&);

        inline void operator+=(const specie&);
        inline void operator*=(const scalar);


    // Friend Operators

        inline friend specie operator+(const specie&, const specie&);
        inline friend specie operator*(const scalar, const specie&);
        inline friend specie operator==(const specie&, const specie&);


    // IOstream Operators

        friend Ostream& operator<<(Ostream&, const specie&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "specie/specieI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
