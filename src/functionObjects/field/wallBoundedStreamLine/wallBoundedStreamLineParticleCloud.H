/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2019-2023 OpenCFD Ltd.
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
    Foam::wallBoundedStreamLineParticleCloud

Description
    A Cloud of wall-bounded streamLine particles

SourceFiles
    streamLineCloud.C

\*---------------------------------------------------------------------------*/

#ifndef Foam_wallBoundedStreamLineParticleCloud_H
#define Foam_wallBoundedStreamLineParticleCloud_H

#include "Cloud/CloudPascal.H"
#include "wallBoundedStreamLine/wallBoundedStreamLineParticle.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                      Class streamLineCloud Declaration
\*---------------------------------------------------------------------------*/

class wallBoundedStreamLineParticleCloud
:
    public Cloud<wallBoundedStreamLineParticle>
{
public:

    //- Type of parcel within the cloud
    typedef wallBoundedStreamLineParticle parcelType;

    // Generated Methods

        //- No copy construct
        wallBoundedStreamLineParticleCloud
        (
            const wallBoundedStreamLineParticleCloud&
        ) = delete;

        //- No copy assignment
        void operator=(const wallBoundedStreamLineParticleCloud&) = delete;


    // Constructors

        //- Read construct
        explicit wallBoundedStreamLineParticleCloud
        (
            const polyMesh& mesh,
            const word& cloudName = cloud::defaultName,
            bool readFields = true
        );

        //- Construct without particles
        wallBoundedStreamLineParticleCloud
        (
            const polyMesh& mesh,
            const Foam::zero,
            const word& cloudName = cloud::defaultName
        )
        :
            Cloud<wallBoundedStreamLineParticle>(mesh, Foam::zero{}, cloudName)
        {}
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
