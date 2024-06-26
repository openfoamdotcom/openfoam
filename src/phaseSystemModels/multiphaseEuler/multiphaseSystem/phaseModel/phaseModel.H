/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
    Copyright (C) 2022 OpenCFD Ltd.
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
    Foam::phaseModel

SourceFiles
    phaseModel.C

\*---------------------------------------------------------------------------*/

#ifndef Foam_multiphaseEuler_phaseModel_H
#define Foam_multiphaseEuler_phaseModel_H

#include "db/dictionary/dictionary.H"
#include "db/dictionary/dictionaryEntry/dictionaryEntry.H"
#include "dimensionedTypes/dimensionedScalar/dimensionedScalar.H"
#include "fields/volFields/volFields.H"
#include "fields/surfaceFields/surfaceFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

namespace multiphaseEuler
{
// Forward declarations
class diameterModel;
}

/*---------------------------------------------------------------------------*\
                           Class phaseModel Declaration
\*---------------------------------------------------------------------------*/

class phaseModel
:
    public volScalarField
{
    // Private data

        //- Name of phase
        word name_;

        dictionary phaseDict_;

        //- Kinematic viscosity
        dimensionedScalar nu_;

        //- Thermal conductivity
        dimensionedScalar kappa_;

        //- Heat capacity
        dimensionedScalar Cp_;

        //- Density
        dimensionedScalar rho_;

        //- Velocity
        volVectorField U_;

        //- Substantive derivative of the velocity
        volVectorField DDtU_;

        //- Volumetric flux of the phase
        surfaceScalarField alphaPhi_;

        //- Volumetric flux for the phase
        autoPtr<surfaceScalarField> phiPtr_;

        //- Diameter model
        autoPtr<multiphaseEuler::diameterModel> dPtr_;


public:

    // Constructors

        phaseModel
        (
            const word& phaseName,
            const dictionary& phaseDict,
            const fvMesh& mesh
        );

        //- Return clone
        autoPtr<phaseModel> clone() const;

        //- Return a pointer to a new phase created on freestore
        //  from Istream
        class iNew
        {
            const fvMesh& mesh_;

        public:

            iNew
            (
                const fvMesh& mesh
            )
            :
                mesh_(mesh)
            {}

            autoPtr<phaseModel> operator()(Istream& is) const
            {
                dictionaryEntry ent(dictionary::null, is);
                return autoPtr<phaseModel>
                (
                    new phaseModel(ent.keyword(), ent, mesh_)
                );
            }
        };


    //- Destructor
    virtual ~phaseModel();


    // Member Functions

        const word& name() const
        {
            return name_;
        }

        const word& keyword() const
        {
            return name();
        }

        tmp<volScalarField> d() const;

        const dimensionedScalar& nu() const
        {
            return nu_;
        }

        const dimensionedScalar& kappa() const
        {
            return kappa_;
        }

        const dimensionedScalar& Cp() const
        {
            return Cp_;
        }

        const dimensionedScalar& rho() const
        {
            return rho_;
        }

        const volVectorField& U() const
        {
            return U_;
        }

        volVectorField& U()
        {
            return U_;
        }

        const volVectorField& DDtU() const
        {
            return DDtU_;
        }

        volVectorField& DDtU()
        {
            return DDtU_;
        }

        const surfaceScalarField& phi() const
        {
            return *phiPtr_;
        }

        surfaceScalarField& phi()
        {
            return *phiPtr_;
        }

        const surfaceScalarField& alphaPhi() const
        {
            return alphaPhi_;
        }

        surfaceScalarField& alphaPhi()
        {
            return alphaPhi_;
        }

        //- Ensure that the flux at inflow/outflow BCs is preserved
        void correctInflowOutflow(surfaceScalarField& alphaPhi) const;

        //- Correct the phase properties
        void correct();

        //-Inherit read from volScalarField
        using volScalarField::read;

        //- Read base transportProperties dictionary
        bool read(const dictionary& phaseDict);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
