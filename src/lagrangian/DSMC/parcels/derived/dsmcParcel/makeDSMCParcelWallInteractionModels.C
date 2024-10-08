/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2015 OpenFOAM Foundation
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

\*---------------------------------------------------------------------------*/

#include "parcels/derived/dsmcParcel/dsmcParcel.H"
#include "clouds/Templates/DSMCCloud/DSMCCloudPascal.H"
#include "submodels/WallInteractionModel/MaxwellianThermal/MaxwellianThermal.H"
#include "submodels/WallInteractionModel/SpecularReflection/SpecularReflection.H"
#include "submodels/WallInteractionModel/MixedDiffuseSpecular/MixedDiffuseSpecular.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    typedef DSMCCloud<dsmcParcel> CloudType;

    makeWallInteractionModel(CloudType);

    // Add instances of wall interaction model to the table
    makeWallInteractionModelType(MaxwellianThermal, CloudType);
    makeWallInteractionModelType(SpecularReflection, CloudType);
    makeWallInteractionModelType(MixedDiffuseSpecular, CloudType);
}


// ************************************************************************* //
