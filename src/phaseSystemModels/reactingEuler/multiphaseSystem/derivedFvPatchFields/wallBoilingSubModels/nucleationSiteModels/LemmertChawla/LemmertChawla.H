/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016-2018 OpenFOAM Foundation
    Copyright (C) 2021 OpenCFD Ltd.
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
    Foam::wallBoilingModels::nucleationSiteModels::LemmertChawla

Description
    A model for nucleation site density based on
    Lemmert-Chawla (1977) function and
    Egorov-Menter (2004) correlation for boiling flows.

    Reference:
    \verbatim
        Lemmert, M., & Chawla, J. M. (1977).
        Influence of flow velocity on surface boiling heat transfer coefficient.
        Heat Transfer in Boiling, 237, 247.

        Egorov, Y., & Menter, F. (2004).
        Experimental implementation of the RPI wall boiling model in CFX-5.6.
        Staudenfeldweg, 12, 83624.
        Technical Report ANSYS/TR-04-10, ANSYS Gmbh.
    \endverbatim

Usage
    Example of the model specification:
    \verbatim
    nucleationSiteModel
    {
        // Mandatory entries
        type            LemmertChawla;

        // Optional entries
        Cn              <scalar>;
    }
    \endverbatim

    where the entries mean:
    \table
      Property  | Description                         | Type | Reqd | Deflt
      type      | Type name: LemmertChawla            | word | yes  | -
      Cn  | Coefficient for nucleation site density | scalar | no   | 1.0
    \endtable

SourceFiles
    LemmertChawla.C

\*---------------------------------------------------------------------------*/

#ifndef LemmertChawla_H
#define LemmertChawla_H

#include "derivedFvPatchFields/wallBoilingSubModels/nucleationSiteModels/nucleationSiteModel/nucleationSiteModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace wallBoilingModels
{
namespace nucleationSiteModels
{

/*---------------------------------------------------------------------------*\
                         Class LemmertChawla Declaration
\*---------------------------------------------------------------------------*/

class LemmertChawla
:
    public nucleationSiteModel
{
    // Private Data

        //- Coefficient for nucleation site density
        scalar Cn_;


    // Private Member Functions

        //- No copy construct
        LemmertChawla(const LemmertChawla&) = delete;

        //- No copy assignment
        void operator=(const LemmertChawla&) = delete;


public:

    //- Runtime type information
    TypeName("LemmertChawla");


    // Constructors

        //- Construct from a dictionary
        LemmertChawla(const dictionary& dict);


    //- Destructor
    virtual ~LemmertChawla() = default;


    // Member Functions

        //- Calculate and return the nucleation-site density
        virtual tmp<scalarField> N
        (
            const phaseModel& liquid,
            const phaseModel& vapor,
            const label patchi,
            const scalarField& Tl,
            const scalarField& Tsatw,
            const scalarField& L
        ) const;

        // I-O

            //- Write
            virtual void write(Ostream& os) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace nucleationSiteModels
} // End namespace wallBoilingModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
