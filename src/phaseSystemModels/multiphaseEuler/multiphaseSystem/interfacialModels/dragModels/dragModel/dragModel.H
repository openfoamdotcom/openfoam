/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2015 OpenFOAM Foundation
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
    Foam::multiphaseEuler::dragModel

Description

SourceFiles
    dragModel.C

\*---------------------------------------------------------------------------*/

#ifndef Foam_multiphaseEuler_dragModel_H
#define Foam_multiphaseEuler_dragModel_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "db/dictionary/dictionary.H"
#include "phaseModel/phaseModel.H"
#include "db/runTimeSelection/construction/runTimeSelectionTables.H"

namespace Foam
{
namespace multiphaseEuler
{

/*---------------------------------------------------------------------------*\
                           Class dragModel Declaration
\*---------------------------------------------------------------------------*/

class dragModel
{
protected:

    // Protected Data

        const dictionary& interfaceDict_;
        const phaseModel& phase1_;
        const phaseModel& phase2_;
        dimensionedScalar residualPhaseFraction_;
        dimensionedScalar residualSlip_;

public:

    //- Runtime type information
    TypeName("dragModel");


    // Declare runtime construction

        declareRunTimeSelectionTable
        (
            autoPtr,
            dragModel,
            dictionary,
            (
                const dictionary& interfaceDict,
                const phaseModel& phase1,
                const phaseModel& phase2
            ),
            (interfaceDict, phase1, phase2)
        );


    // Constructors

        dragModel
        (
            const dictionary& dict,
            const phaseModel& phase1,
            const phaseModel& phase2
        );


    //- Destructor
    virtual ~dragModel() = default;


    // Selectors

        static autoPtr<dragModel> New
        (
            const dictionary& dict,
            const phaseModel& phase1,
            const phaseModel& phase2
        );


    // Member Functions

        const phaseModel& phase1() const
        {
            return phase1_;
        }

        const phaseModel& phase2() const
        {
            return phase2_;
        }

        const dimensionedScalar& residualPhaseFraction() const
        {
            return residualPhaseFraction_;
        }

        const dimensionedScalar& residualSlip() const
        {
            return residualSlip_;
        }

        //- The drag function K used in the momentum eq.
        //    ddt(alpha1*rho1*U1) + ... = ... alpha1*alpha2*K*(U1-U2)
        //    ddt(alpha2*rho2*U2) + ...  = ... alpha1*alpha2*K*(U2-U1)
        // ********************************** NB! *****************************
        // for numerical reasons alpha1 and alpha2 has been
        // extracted from the dragFunction K,
        // so you MUST divide K by alpha1*alpha2 when implementing the drag
        // function
        // ********************************** NB! *****************************
        virtual tmp<volScalarField> K(const volScalarField& Ur) const = 0;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace multiphaseEuler
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
