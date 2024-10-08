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
    Foam::constAnIsoSolidTransport

Description
    Constant properties Transport package.
    Templated into a given Thermodynamics package (needed for thermal
    conductivity).

SourceFiles
    constAnIsoSolidTransportI.H
    constAnIsoSolidTransport.C

\*---------------------------------------------------------------------------*/

#ifndef constAnIsoSolidTransport_H
#define constAnIsoSolidTransport_H

#include "primitives/Vector/floats/vector.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
// Forward Declarations
template<class Thermo> class constAnIsoSolidTransport;

template<class Thermo>
inline constAnIsoSolidTransport<Thermo> operator*
(
    const scalar,
    const constAnIsoSolidTransport<Thermo>&
);

template<class Thermo>
Ostream& operator<<
(
    Ostream&,
    const constAnIsoSolidTransport<Thermo>&
);


/*---------------------------------------------------------------------------*\
                   Class constAnIsoSolidTransport Declaration
\*---------------------------------------------------------------------------*/

template<class Thermo>
class constAnIsoSolidTransport
:
    public Thermo
{
    // Private Data

        //- Constant anisotropic thermal conductivity.
        vector kappa_;


    // Private Member Functions

        //- Construct from components
        inline constAnIsoSolidTransport(const Thermo& t, const vector kappa);


public:

    // Generated Methods: copy construct, copy assignment


    // Constructors

        //- Construct as named copy
        inline constAnIsoSolidTransport
        (
            const word&,
            const constAnIsoSolidTransport&
        );

        //- Construct from dictionary
        explicit constAnIsoSolidTransport(const dictionary& dict);

        // Selector from dictionary
        inline static autoPtr<constAnIsoSolidTransport> New
        (
            const dictionary& dict
        );


    // Member Functions

        //- Return the instantiated type name
        static word typeName()
        {
            return "constAnIso<" + Thermo::typeName() + '>';
        }

        //- Is the thermal conductivity isotropic
        static const bool isotropic = false;

        //- Isotropic thermal conductivity [W/mK]
        inline scalar kappa(const scalar p, const scalar T) const;

        //- Un-isotropic thermal conductivity [W/mK]
        inline vector Kappa(const scalar p, const scalar T) const;

        //- Dynamic viscosity [kg/ms]
        inline scalar mu(const scalar p, const scalar T) const;

        //- Thermal diffusivity of enthalpy [kg/ms]
        inline vector alphah(const scalar p, const scalar T) const;


        //- Write to Ostream
        void write(Ostream& os) const;


    // Member Operators

        inline void operator+=(const constAnIsoSolidTransport&);


    // Friend Operators

        friend constAnIsoSolidTransport operator* <Thermo>
        (
            const scalar,
            const constAnIsoSolidTransport&
        );


    // IOstream Operators

        friend Ostream& operator<< <Thermo>
        (
            Ostream&,
            const constAnIsoSolidTransport&
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "transport/const/constAnIsoSolidTransportI.H"

#ifdef NoRepository
    #include "transport/const/constAnIsoSolidTransport.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
