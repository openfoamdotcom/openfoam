/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2015-2018 OpenFOAM Foundation
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
    Foam::MultiComponentPhaseModel

Description
    Class which represents a phase with multiple species. Returns the species'
    mass fractions, and their governing equations.

SourceFiles
    MultiComponentPhaseModel.C

\*---------------------------------------------------------------------------*/

#ifndef MultiComponentPhaseModel_H
#define MultiComponentPhaseModel_H

#include "phaseModel/phaseModel/reactingEuler_phaseModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                   Class MultiComponentPhaseModel Declaration
\*---------------------------------------------------------------------------*/

template<class BasePhaseModel>
class MultiComponentPhaseModel
:
    public BasePhaseModel
{
protected:

    // Protected data

        //- Turbulent Schmidt number
        dimensionedScalar Sct_;

        //- Residual phase fraction
        dimensionedScalar residualAlpha_;

        //- Inert species index
        label inertIndex_;

        //- Pointer list to active species
        UPtrList<volScalarField> YActive_;


public:

    // Constructors

        MultiComponentPhaseModel
        (
            const phaseSystem& fluid,
            const word& phaseName,
            const label index
        );


    //- Destructor
    virtual ~MultiComponentPhaseModel();


    // Member Functions

        //- Correct the thermodynamics
        virtual void correctThermo();

        // Species

            //- Return whether the phase is pure (i.e., not multi-component)
            virtual bool pure() const;

            //- Return the species fraction equation
            virtual tmp<fvScalarMatrix> YiEqn(volScalarField& Yi);

            //- Return the species mass fractions
            virtual const PtrList<volScalarField>& Y() const;

            //- Return a species mass fraction by name
            virtual const volScalarField& Y(const word& name) const;

            //- Access the species mass fractions
            virtual PtrList<volScalarField>& YRef();

            //- Return the active species mass fractions
            virtual const UPtrList<volScalarField>& YActive() const;

            //- Access the active species mass fractions
            virtual UPtrList<volScalarField>& YActiveRef();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "phaseModel/MultiComponentPhaseModel/MultiComponentPhaseModel.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
