/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2012 OpenFOAM Foundation
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
    Foam::patchCloudSet

Description
    Like Foam::cloudSet but samples nearest patch face

    For a dictionary specification:
    \table
        Property | Description                             | Required | Default
        type     | patchCloud                              | yes      |
        axis     | x, y, z, xyz, distance                  | yes      |
        patches  | List of patch names or regexs           | yes      |
        points   | List of selected locations              | yes      |
        maxDistance | Max search distance                  | yes      |
    \endtable

SourceFiles
    patchCloudSet.C

\*---------------------------------------------------------------------------*/

#ifndef patchCloudSet_H
#define patchCloudSet_H

#include "sampledSet/sampledSet/sampledSet.H"
#include "containers/Lists/DynamicList/DynamicList.H"
#include "containers/HashTables/HashSet/HashSet.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class patchCloudSet Declaration
\*---------------------------------------------------------------------------*/

class patchCloudSet
:
    public sampledSet
{
    // Private data

        //- Sampling points
        const pointField sampleCoords_;

        //- Patches to sample
        const labelHashSet patchSet_;

        //- Maximum distance to look for nearest
        const scalar searchDist_;


    // Private Member Functions

        //- Samples all points in sampleCoords.
        void calcSamples
        (
            DynamicList<point>& samplingPts,
            DynamicList<label>& samplingCells,
            DynamicList<label>& samplingFaces,
            DynamicList<label>& samplingSegments,
            DynamicList<scalar>& samplingCurveDist
        ) const;

        //- Uses calcSamples to obtain samples. Copies them into *this.
        void genSamples();


public:

    //- Runtime type information
    TypeName("patchCloud");


    // Constructors

        //- Construct from components
        patchCloudSet
        (
            const word& name,
            const polyMesh& mesh,
            const meshSearch& searchEngine,
            const word& axis,
            const List<point>& sampleCoords,
            const labelHashSet& patchSet,
            const scalar searchDist
        );

        //- Construct from dictionary
        patchCloudSet
        (
            const word& name,
            const polyMesh& mesh,
            const meshSearch& searchEngine,
            const dictionary& dict
        );


    //- Destructor
    virtual ~patchCloudSet() = default;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
