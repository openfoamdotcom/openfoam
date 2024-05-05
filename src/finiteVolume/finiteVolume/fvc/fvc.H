/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011 OpenFOAM Foundation
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

Namespace
    Foam::fvc

Description
    Namespace of functions to calculate explicit derivatives.

\*---------------------------------------------------------------------------*/

#ifndef fvc_H
#define fvc_H

#include "finiteVolume/fv/fv.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "interpolation/surfaceInterpolation/surfaceInterpolation/surfaceInterpolate.H"
#include "finiteVolume/fvc/fvcVolumeIntegrate.H"
#include "finiteVolume/fvc/fvcSurfaceIntegrate.H"
#include "finiteVolume/fvc/fvcAverage.H"
#include "finiteVolume/fvc/fvcReconstruct.H"
#include "finiteVolume/fvc/fvcDdt.H"
#include "finiteVolume/fvc/fvcDDtDeCased.H"
#include "finiteVolume/fvc/fvcD2dt2.H"
#include "finiteVolume/fvc/fvcDiv.H"
#include "finiteVolume/fvc/fvcFlux.H"
#include "finiteVolume/fvc/fvcGrad.H"
#include "finiteVolume/fvc/fvcMagSqrGradGrad.H"
#include "finiteVolume/fvc/fvcSnGrad.H"
#include "finiteVolume/fvc/fvcCurl.H"
#include "finiteVolume/fvc/fvcLaplacian.H"
#include "finiteVolume/fvc/fvcSup.H"
#include "finiteVolume/fvc/fvcMeshPhi.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
