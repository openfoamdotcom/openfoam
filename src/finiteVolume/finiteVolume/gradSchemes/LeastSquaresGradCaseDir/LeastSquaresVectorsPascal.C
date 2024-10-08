/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2013-2016 OpenFOAM Foundation
    Copyright (C) 2020-2021 OpenCFD Ltd.
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

#include "finiteVolume/gradSchemes/LeastSquaresGradCaseDir/LeastSquaresVectorsPascal.H"

// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //

template<class Stencil>
Foam::fv::LeastSquaresVectors<Stencil>::LeastSquaresVectors
(
    const fvMesh& mesh
)
:
    MeshObject<fvMesh, Foam::MoveableMeshObject, LeastSquaresVectors>(mesh),
    vectors_(mesh.nCells())
{
    calcLeastSquaresVectors();
}


// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

template<class Stencil>
Foam::fv::LeastSquaresVectors<Stencil>::~LeastSquaresVectors()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Stencil>
void Foam::fv::LeastSquaresVectors<Stencil>::calcLeastSquaresVectors()
{
    DebugInFunction << "Calculating least square gradient vectors" << nl;

    const fvMesh& mesh = this->mesh_;
    const extendedCentredCellToCellStencil& stencil = this->stencil();

    stencil.collectData(mesh.C(), vectors_);

    // Create the base form of the dd-tensor
    // including components for the "empty" directions
    const symmTensor dd0(sqr((Vector<label>::one - mesh.geometricD())/2));

    forAll(vectors_, i)
    {
        List<vector>& lsvi = vectors_[i];
        symmTensor dd(dd0);

        // The current cell is 0 in the stencil
        // Calculate the deltas and sum the weighted dd
        for (label j = 1; j < lsvi.size(); ++j)
        {
            lsvi[j] = lsvi[j] - lsvi[0];
            const scalar magSqrLsvi = magSqr(lsvi[j]);
            dd += sqr(lsvi[j])/magSqrLsvi;
            lsvi[j] /= magSqrLsvi;
        }

        // Invert dd
        dd = inv(dd);

        // Remove the components corresponding to the empty directions
        dd -= dd0;

        // Finalize the gradient weighting vectors
        lsvi[0] = Zero;
        for (label j = 1; j < lsvi.size(); ++j)
        {
            lsvi[j] = dd & lsvi[j];
            lsvi[0] -= lsvi[j];
        }
    }

    DebugInfo
        << "Finished calculating least square gradient vectors" << endl;
}


template<class Stencil>
bool Foam::fv::LeastSquaresVectors<Stencil>::movePoints()
{
    calcLeastSquaresVectors();
    return true;
}


// ************************************************************************* //
