/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2012-2015 OpenFOAM Foundation
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
    Foam::faceAreaWeightModel

Description
    Abstract base class for providing faceAreaWeight values to the cell motion
    controller based on an argument faceAreaFraction value, typically the ratio
    of the area of the face in question to the area of a square face with a side
    length of the local target cell size.

SourceFiles
    faceAreaWeightModel.C

\*---------------------------------------------------------------------------*/

#ifndef faceAreaWeightModel_H
#define faceAreaWeightModel_H

#include "meshes/primitiveShapes/point/point.H"
#include "db/dictionary/dictionary.H"
#include "memory/autoPtr/autoPtr.H"
#include "db/runTimeSelection/construction/runTimeSelectionTables.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                       Class faceAreaWeightModel Declaration
\*---------------------------------------------------------------------------*/

class faceAreaWeightModel
:
    public dictionary
{

protected:

    // Protected data

        //- Method coeffs dictionary
        dictionary coeffDict_;


    // Protected Member Functions

        //- No copy construct
        faceAreaWeightModel(const faceAreaWeightModel&) = delete;

        //- No copy assignment
        void operator=(const faceAreaWeightModel&) = delete;


public:

    //- Runtime type information
    TypeName("faceAreaWeightModel");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            faceAreaWeightModel,
            dictionary,
            (
                const dictionary& faceAreaWeightDict
            ),
            (faceAreaWeightDict)
        );


    // Constructors

        //- Construct from components
        faceAreaWeightModel
        (
            const word& type,
            const dictionary& faceAreaWeightDict
        );


    // Selectors

        //- Return a reference to the selected faceAreaWeightModel
        static autoPtr<faceAreaWeightModel> New
        (
            const dictionary& faceAreaWeightDict
        );


    //- Destructor
    virtual ~faceAreaWeightModel() = default;


    // Member Functions

        //- Const access to the coeffs dictionary
        const dictionary& coeffDict() const
        {
            return coeffDict_;
        }

        //- Return the current faceAreaWeight coefficient
        virtual scalar faceAreaWeight(scalar faceAreaFraction) const = 0;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
