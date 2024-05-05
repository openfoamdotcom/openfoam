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
    Foam::basicSprayCloud

Description
    Cloud class to introduce reacting spray parcels

\*---------------------------------------------------------------------------*/

#ifndef basicSprayCloud_H
#define basicSprayCloud_H

#include "Cloud/CloudPascal.H"
#include "clouds/Templates/KinematicCloud/KinematicCloudPascal.H"
#include "clouds/Templates/ThermoCloud/ThermoCloudPascal.H"
#include "clouds/Templates/ReactingCloud/ReactingCloudPascal.H"
#include "clouds/Templates/SprayCloud/SprayCloudPascal.H"
#include "parcels/derived/basicSprayParcel/basicSprayParcel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    typedef SprayCloud
    <
        ReactingCloud
        <
            ThermoCloud
            <
                KinematicCloud
                <
                    Cloud
                    <
                        basicSprayParcel
                    >
                >
            >
        >
    > basicSprayCloud;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
