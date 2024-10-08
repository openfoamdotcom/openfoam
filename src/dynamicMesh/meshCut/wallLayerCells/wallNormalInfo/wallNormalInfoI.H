/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2020 OpenCFD Ltd.
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

#include "meshes/polyMesh/polyMesh.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Update this with w2 if not yet set.
template<class TrackingData>
inline bool Foam::wallNormalInfo::update
(
    const wallNormalInfo& w2,
    TrackingData& td
)
{
    if (!w2.valid(td))
    {
        FatalErrorInFunction
          << "Problem: w2 is not valid" << abort(FatalError);

        return false;
    }
    else if (valid(td))
    {
        // our already set. Stop any transfer
        return false;
    }
    else
    {
        normal_ = w2.normal();

        return true;
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline Foam::wallNormalInfo::wallNormalInfo()
:
    normal_(point::max)
{}


inline Foam::wallNormalInfo::wallNormalInfo(const vector& normal)
:
    normal_(normal)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class TrackingData>
inline bool Foam::wallNormalInfo::valid(TrackingData& td) const
{
    return normal_ != point::max;
}


// No geometric data so never any problem on cyclics
template<class TrackingData>
inline bool Foam::wallNormalInfo::sameGeometry
(
    const polyMesh&,
    const wallNormalInfo& w2,
    const scalar tol,
    TrackingData& td
) const
{
    return true;
}


// No geometric data.
template<class TrackingData>
inline void Foam::wallNormalInfo::leaveDomain
(
    const polyMesh&,
    const polyPatch& patch,
    const label patchFacei,
    const point& faceCentre,
    TrackingData& td
)
{}


// No geometric data.
template<class TrackingData>
inline void Foam::wallNormalInfo::transform
(
    const polyMesh&,
    const tensor& rotTensor,
    TrackingData& td
)
{}


// No geometric data.
template<class TrackingData>
inline void Foam::wallNormalInfo::enterDomain
(
    const polyMesh&,
    const polyPatch& patch,
    const label patchFacei,
    const point& faceCentre,
    TrackingData& td
)
{}


// Update this with w2 if w2 nearer to pt.
template<class TrackingData>
inline bool Foam::wallNormalInfo::updateCell
(
    const polyMesh&,
    const label thisCelli,
    const label neighbourFacei,
    const wallNormalInfo& neighbourWallInfo,
    const scalar tol,
    TrackingData& td
)
{
    return update(neighbourWallInfo, td);
}


// Update this with w2 if w2 nearer to pt.
template<class TrackingData>
inline bool Foam::wallNormalInfo::updateFace
(
    const polyMesh&,
    const label thisFacei,
    const label neighbourCelli,
    const wallNormalInfo& neighbourWallInfo,
    const scalar tol,
    TrackingData& td
)
{
    return update(neighbourWallInfo, td);
}


// Update this with w2 if w2 nearer to pt.
template<class TrackingData>
inline bool Foam::wallNormalInfo::updateFace
(
    const polyMesh&,
    const label thisFacei,
    const wallNormalInfo& neighbourWallInfo,
    const scalar tol,
    TrackingData& td
)
{
    return update(neighbourWallInfo, td);
}


template<class TrackingData>
inline bool Foam::wallNormalInfo::equal
(
    const wallNormalInfo& rhs,
    TrackingData& td
) const
{
    return operator==(rhs);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool Foam::wallNormalInfo::operator==
(
    const wallNormalInfo& rhs
) const
{
    return normal_ == rhs.normal_;
}


inline bool Foam::wallNormalInfo::operator!=
(
    const wallNormalInfo& rhs
) const
{
    return !(*this == rhs);
}


// ************************************************************************* //
