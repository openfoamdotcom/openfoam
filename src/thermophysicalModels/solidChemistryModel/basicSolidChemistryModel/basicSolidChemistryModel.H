/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2013-2017 OpenFOAM Foundation
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
    Foam::basicSolidChemistryModel

Description
    Chemistry model for solid thermodynamics

SourceFiles
    basicSolidChemistryModelI.H
    basicSolidChemistryModel.C
    basicSolidChemistryModelNew.C

\*---------------------------------------------------------------------------*/

#ifndef basicSolidChemistryModel_H
#define basicSolidChemistryModel_H

#include "chemistryModel/basicChemistryModel/basicChemistryModel.H"
#include "memory/autoPtr/autoPtr.H"
#include "db/runTimeSelection/construction/runTimeSelectionTables.H"
#include "solidReactionThermo/solidReactionThermo.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward Declarations
class fvMesh;

/*---------------------------------------------------------------------------*\
                     Class basicSolidChemistryModel Declaration
\*---------------------------------------------------------------------------*/

class basicSolidChemistryModel
:
    public basicChemistryModel
{
    // Private Member Functions

        //- Construct as copy (not implemented)
        basicSolidChemistryModel(const basicSolidChemistryModel&);

        //- No copy assignment
        void operator=(const basicSolidChemistryModel&) = delete;


protected:

    // Protected Data

        //- Solid thermo
        solidReactionThermo& solidThermo_;


public:

    //- Runtime type information
    TypeName("basicSolidChemistryModel");


    //- Thermo type
    typedef solidReactionThermo reactionThermo;


    //- Declare run-time constructor selection tables
    declareRunTimeSelectionTable
    (
        autoPtr,
        basicSolidChemistryModel,
        thermo,
        (solidReactionThermo& thermo),
        (thermo)
    );


    // Constructors

        //- Construct from thermo
        basicSolidChemistryModel(solidReactionThermo& thermo);


    //- Selector
    static autoPtr<basicSolidChemistryModel> New(solidReactionThermo& thermo);


    //- Destructor
    virtual ~basicSolidChemistryModel();


    // Member Functions

        //- Return access to the solid thermo package
        inline solidReactionThermo& solidThermo();

        //- Return const access to the solid thermo package
        inline const solidReactionThermo& solidThermo() const;

        //- Return total gases mass source term [kg/m3/s]
        virtual tmp<volScalarField::Internal> RRg() const = 0;

        //- Return total solids mass source term [kg/m3/s]
        virtual tmp<volScalarField::Internal> RRs() const = 0;

        //- Return chemical source terms for solids [kg/m3/s]
        virtual const volScalarField::Internal& RRs
        (
            const label i
        ) const = 0;

        //- Return chemical source terms for gases [kg/m3/s]
        virtual const volScalarField::Internal& RRg
        (
            const label i
        ) const = 0;

        //- Returns the reaction rate of the speciei in reactionI
        virtual tmp<volScalarField::Internal> calculateRR
        (
            const label reactionI,
            const label speciei
        ) const;

        //- Return sensible enthalpy for gas i [J/Kg]
        virtual tmp<volScalarField> gasHs
        (
            const volScalarField& p,
            const volScalarField& T,
            const label i
        ) const = 0;

        //- Return net solid sensible enthalpy [J/Kg]
        virtual tmp<DimensionedField<scalar, volMesh>> RRsHs() const = 0;

        //- Return specie Table for gases
        virtual const speciesTable& gasTable() const = 0;

        //- Set reacting status of cell, celli
        virtual void setCellReacting(const label celli, const bool active) = 0;

        //- Calculates the reaction rates
        virtual void calculate() = 0;

        //- Return const access to the total source terms
        virtual const volScalarField::Internal& RR
        (
            const label i
        ) const;

        //- Return non-const access to the total source terms
        virtual volScalarField::Internal& RR(const label i);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "basicSolidChemistryModel/basicSolidChemistryModelI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
