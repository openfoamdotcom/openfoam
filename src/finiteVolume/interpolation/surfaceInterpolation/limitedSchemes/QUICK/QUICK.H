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

Class
    Foam::QUICKLimiter

Group
    grpFvLimitedSurfaceInterpolationSchemes

Description
    Class with limiter function which returns the limiter for the
    quadratic-upwind differencing scheme.

    Note that the weighting factors are not bounded between upwind and
    central-differencing, some downwind contribution is possible although
    the interpolate is limited to be between the upwind and downwind cell
    values.

    Used in conjunction with the template class LimitedScheme.

SourceFiles
    QUICK.C

\*---------------------------------------------------------------------------*/

#ifndef QUICK_H
#define QUICK_H

#include "primitives/Vector/floats/vector.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class QUICKLimiter Declaration
\*---------------------------------------------------------------------------*/

template<class LimiterFunc>
class QUICKLimiter
:
    public LimiterFunc
{

public:

    QUICKLimiter(Istream&)
    {}

    scalar limiter
    (
        const scalar cdWeight,
        const scalar faceFlux,
        const typename LimiterFunc::phiType& phiP,
        const typename LimiterFunc::phiType& phiN,
        const typename LimiterFunc::gradPhiType& gradcP,
        const typename LimiterFunc::gradPhiType& gradcN,
        const vector& d
    ) const
    {
        scalar phiCD = cdWeight*phiP + (1 - cdWeight)*phiN;

        scalar phiU, phif;

        if (faceFlux > 0)
        {
            phiU = phiP;
            phif = 0.5*(phiCD + phiP + (1 - cdWeight)*(d & gradcP));
        }
        else
        {
            phiU = phiN;
            phif = 0.5*(phiCD + phiN - cdWeight*(d & gradcN));
        }

        // Calculate the effective limiter for the QUICK interpolation
        scalar QLimiter = (phif - phiU)/stabilise(phiCD - phiU, SMALL);

        // Limit the limiter between upwind and downwind
        return clamp(QLimiter, 0, 2);
    }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
