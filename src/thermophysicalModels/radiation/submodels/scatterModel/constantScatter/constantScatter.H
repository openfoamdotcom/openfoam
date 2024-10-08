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

Class
    Foam::radiation::constantScatter

Group
    grpRadiationScatterSubModels

Description
    Constant radiation scatter coefficient

SourceFiles
    scatterModel.C

\*---------------------------------------------------------------------------*/

#ifndef radiation_constantScatter_H
#define radiation_constantScatter_H

#include "submodels/scatterModel/scatterModel/scatterModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace radiation
{

/*---------------------------------------------------------------------------*\
                       Class constantScatter Declaration
\*---------------------------------------------------------------------------*/

class constantScatter
:
    public scatterModel
{

    // Private data

        //- Coefficients dictionary
        dictionary coeffsDict_;

        //- Scattering coefficient / [1/m]
        dimensionedScalar sigma_;

        //- Linear-anisotropic phase function coefficient / []
        //  -1 < C < 1
        //  - = backward scattering
        //  0 = isotropic scattering (reasonable default value)
        //  + = forward scattering
        dimensionedScalar C_;


public:

    //- Runtime type information
    TypeName("constantScatter");


    // Constructors

        //- Construct from components
        constantScatter(const dictionary& dict, const fvMesh& mesh);


    //- Destructor
    virtual ~constantScatter() = default;


    // Member Functions

        //- Return scatter coefficient
        tmp<volScalarField> sigmaEff() const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace radiation
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
