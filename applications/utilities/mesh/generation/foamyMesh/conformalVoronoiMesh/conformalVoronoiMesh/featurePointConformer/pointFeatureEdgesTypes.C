/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2013-2015 OpenFOAM Foundation
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

#include "conformalVoronoiMesh/featurePointConformer/pointFeatureEdgesTypes.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::pointFeatureEdgesTypes::pointFeatureEdgesTypes
(
    const extendedFeatureEdgeMesh& feMesh,
    const label pointLabel
)
:
    HashTable<label, extendedFeatureEdgeMesh::edgeStatus, Hash<label>>(),
    feMesh_(feMesh),
    pointLabel_(pointLabel)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Foam::List<Foam::extendedFeatureEdgeMesh::edgeStatus>
Foam::pointFeatureEdgesTypes::calcPointFeatureEdgesTypes()
{
    const labelList& pEds = feMesh_.pointEdges()[pointLabel_];

    List<extendedFeatureEdgeMesh::edgeStatus> allEdStat(pEds.size());

    forAll(pEds, i)
    {
        label edgeI = pEds[i];

        extendedFeatureEdgeMesh::edgeStatus& eS = allEdStat[i];

        eS = feMesh_.getEdgeStatus(edgeI);

        this->operator()(eS)++;
    }

    return allEdStat;
}


// * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * * //

Foam::Ostream& Foam::operator<<
(
    Ostream& os,
    const pointFeatureEdgesTypes& p
)
{
    os  << "Point = " << p.pointLabel_ << endl;

    forAllConstIters(p, iter)
    {
        os  << "    "
            << extendedFeatureEdgeMesh::edgeStatusNames_[iter.key()]
            << " = "
            << iter.val()
            << endl;
    }

    return os;
}


// ************************************************************************* //
