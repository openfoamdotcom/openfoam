/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2014-2015 OpenFOAM Foundation
    Copyright (C) 2019 OpenCFD Ltd.
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

Namespace
    Foam::mixtureViscosityModels

Description
    A namespace for incompressible mixtureViscosityModel implementations.

Class
    Foam::mixtureViscosityModel

Description
    An abstract base class for incompressible mixtureViscosityModels.

SourceFiles
    mixtureViscosityModel.C
    mixtureViscosityModelNew.C

\*---------------------------------------------------------------------------*/

#ifndef mixtureViscosityModel_H
#define mixtureViscosityModel_H

#include "db/dictionary/dictionary.H"
#include "fields/volFields/volFieldsFwd.H"
#include "fields/surfaceFields/surfaceFieldsFwd.H"
#include "dimensionedTypes/dimensionedScalar/dimensionedScalar.H"
#include "db/runTimeSelection/construction/runTimeSelectionTables.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                Class mixtureViscosityModel Declaration
\*---------------------------------------------------------------------------*/

class mixtureViscosityModel
{

protected:

    // Protected data

        word name_;
        dictionary viscosityProperties_;

        const volVectorField& U_;
        const surfaceScalarField& phi_;


    // Private Member Functions

        //- No copy construct
        mixtureViscosityModel(const mixtureViscosityModel&) = delete;

        //- No copy assignment
        void operator=(const mixtureViscosityModel&) = delete;


public:

    //- Runtime type information
    TypeName("mixtureViscosityModel");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            mixtureViscosityModel,
            dictionary,
            (
                const word& name,
                const dictionary& viscosityProperties,
                const volVectorField& U,
                const surfaceScalarField& phi
            ),
            (name, viscosityProperties, U, phi)
        );


    // Selectors

        //- Return a reference to the selected viscosity model
        static autoPtr<mixtureViscosityModel> New
        (
            const word& name,
            const dictionary& viscosityProperties,
            const volVectorField& U,
            const surfaceScalarField& phi
        );


    // Constructors

        //- Construct from components
        mixtureViscosityModel
        (
            const word& name,
            const dictionary& viscosityProperties,
            const volVectorField& U,
            const surfaceScalarField& phi
        );


    //- Destructor
    virtual ~mixtureViscosityModel() = default;


    // Member Functions

        //- Return the phase transport properties dictionary
        const dictionary& viscosityProperties() const
        {
            return viscosityProperties_;
        }

        //- Return the mixture viscosity
        //  given the viscosity of the continuous phase
        virtual tmp<volScalarField> mu(const volScalarField& muc) const = 0;

        //- Read transportProperties dictionary
        virtual bool read(const dictionary& viscosityProperties) = 0;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
