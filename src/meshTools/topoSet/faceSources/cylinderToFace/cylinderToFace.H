/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2017 OpenFOAM Foundation
    Copyright (C) 2018-2022 OpenCFD Ltd.
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
    Foam::cylinderToFace

Description
    A \c topoSetFaceSource to select all faces whose face centre
    inside a given bounding cylinder or cylinder annulus.

    Operands:
    \table
      Operand   | Type    | Location
      output    | faceSet | $FOAM_CASE/constant/polyMesh/sets/\<set\>
    \endtable

Usage
    Minimal example by using \c system/topoSetDict.actions:
    \verbatim
    {
        // Mandatory (inherited) entries
        name           <name>;
        type           faceSet;
        action         <action>;

        // Mandatory entries
        source         cylinderToFace;
        point1         (<p1X> <p1Y> <p1Z>);
        point2         (<p2X> <p2Y> <p2Z>);
        radius         <radius1>;   // or outerRadius

        // Optional entries
        innerRadius    <radius2>;
    }
    \endverbatim

    where the entries mean:
    \table
      Property   | Description                            | Type | Req'd | Dflt
      name       | Name of faceSet                        | word | yes  | -
      type       | Type name: faceSet                     | word | yes  | -
      action     | Action applied on faces - see below    | word | yes  | -
      source     | Source name: cylinderToFace            | word | yes  | -
      point1 (p1) | Coordinate of the first endpoint      | vector | yes | -
      point2 (p2) | Coordinate of the second endpoint     | vector | yes | -
      radius      | Cylinder outer radius                 | scalar | yes | -
      innerRadius | Cylinder inner radius                 | scalar | no  | 0
      outerRadius | Alternative spelling for 'radius'     | scalar | no  | -
    \endtable

    Options for the \c action entry:
    \verbatim
      new      | Create a new faceSet from selected faces
      add      | Add selected faces into this faceSet
      subtract | Remove selected faces from this faceSet
    \endverbatim

See also
    - Foam::topoSetSource
    - Foam::topoSetFaceSource
    - Foam::cylinderAnnulusToFace

SourceFiles
    cylinderToFace.C

\*---------------------------------------------------------------------------*/

#ifndef Foam_cylinderToFace_H
#define Foam_cylinderToFace_H

#include "topoSet/faceSources/topoSetFaceSource/topoSetFaceSource.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                       Class cylinderToFace Declaration
\*---------------------------------------------------------------------------*/

class cylinderToFace
:
    public topoSetFaceSource
{
    // Private Data

        //- Add usage string
        static addToUsageTable usage_;

        //- First point on cylinder axis
        point point1_;

        //- Second point on cylinder axis
        point point2_;

        //- Outer radius
        scalar radius_;

        //- Inner radius
        scalar innerRadius_;


    // Private Member Functions

        void combine(topoSet& set, const bool add) const;

protected:

    // Constructors

        //- Construct from Istream with mandatory inner radius
        cylinderToFace
        (
            const polyMesh& mesh,
            Istream& is,
            const bool mandatoryInnerRadius
        );


public:

    //- Runtime type information
    TypeName("cylinderToFace");


    // Constructors

        //- Construct from components
        cylinderToFace
        (
            const polyMesh& mesh,
            const point& point1,
            const point& point2,
            const scalar radius,
            const scalar innerRadius = 0
        );

        //- Construct from dictionary
        cylinderToFace(const polyMesh& mesh, const dictionary& dict);

        //- Construct from Istream
        cylinderToFace(const polyMesh& mesh, Istream& is);


    //- Destructor
    virtual ~cylinderToFace() = default;


    // Member Functions

        virtual void applyToSet
        (
            const topoSetSource::setAction action,
            topoSet& set
        ) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
