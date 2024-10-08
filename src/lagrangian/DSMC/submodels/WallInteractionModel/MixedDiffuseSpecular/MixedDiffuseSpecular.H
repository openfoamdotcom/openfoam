/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
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
    Foam::MixedDiffuseSpecular

Description
    Wall interaction setting microscopic velocity to a random one
    drawn from a Maxwellian distribution corresponding to a specified
    temperature for a specified fraction of collisions, and reversing
    the wall-normal component of the particle velocity for the
    remainder.

\*---------------------------------------------------------------------------*/

#ifndef MixedDiffuseSpecular_H
#define MixedDiffuseSpecular_H

#include "submodels/WallInteractionModel/WallInteractionModel/WallInteractionModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
/*---------------------------------------------------------------------------*\
                    Class MixedDiffuseSpecular Declaration
\*---------------------------------------------------------------------------*/

template<class CloudType>
class MixedDiffuseSpecular
:
    public WallInteractionModel<CloudType>
{
    // Private data

        //- Fraction of wall interactions that are diffuse
        scalar diffuseFraction_;


public:

    //- Runtime type information
    TypeName("MixedDiffuseSpecular");


    // Constructors

        //- Construct from dictionary
        MixedDiffuseSpecular
        (
            const dictionary& dict,
            CloudType& cloud
        );


    //- Destructor
    virtual ~MixedDiffuseSpecular();


    // Member Functions

        //- Apply wall correction
        virtual void correct(typename CloudType::parcelType& p);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "submodels/WallInteractionModel/MixedDiffuseSpecular/MixedDiffuseSpecular.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
