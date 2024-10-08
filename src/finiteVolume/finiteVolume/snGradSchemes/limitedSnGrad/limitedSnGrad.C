/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2021 OpenCFD Ltd.
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

#include "finiteVolume/fv/fv.H"
#include "finiteVolume/snGradSchemes/limitedSnGrad/limitedSnGrad.H"
#include "fields/volFields/volFields.H"
#include "fields/surfaceFields/surfaceFields.H"
#include "interpolation/surfaceInterpolation/schemes/localMax/localMax.H"
#include "finiteVolume/fvc/fvcCellReduce.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace fv
{

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
limitedSnGrad<Type>::correction
(
    const GeometricField<Type, fvPatchField, volMesh>& vf
) const
{
    const GeometricField<Type, fvsPatchField, surfaceMesh> corr
    (
        correctedScheme_().correction(vf)
    );

    const surfaceScalarField limiter
    (
        min
        (
            limitCoeff_
           *mag(snGradScheme<Type>::snGrad(vf, deltaCoeffs(vf), "SndGrad"))
           /(
                (1 - limitCoeff_)*mag(corr)
              + dimensionedScalar("small", corr.dimensions(), SMALL)
            ),
            dimensionedScalar("one", dimless, 1.0)
        )
    );

    if (fv::debug)
    {
        InfoInFunction
            << "limiter min: " << min(limiter.primitiveField())
            << " max: "<< max(limiter.primitiveField())
            << " avg: " << average(limiter.primitiveField()) << endl;


        if (fv::debug & 2)
        {
            static scalar oldTime = -1;
            static label subIter = 0;
            if (vf.mesh().time().value() != oldTime)
            {
                oldTime = vf.mesh().time().value();
                subIter = 0;
            }
            else
            {
                ++subIter;
            }
            word fieldName("limiter_" + Foam::name(subIter));

            GeometricField<scalar, fvPatchField, volMesh> volLimiter
            (
                IOobject
                (
                    fieldName,
                    vf.mesh().time().timeName(),
                    vf.mesh().thisDb(),
                    IOobject::NO_READ,
                    IOobject::NO_WRITE,
                    IOobject::NO_REGISTER
                ),
                fvc::cellReduce(limiter, minEqOp<scalar>(), scalar(1))
            );
            Info<< "Writing limiter field to " << volLimiter.objectPath()
                << endl;
            volLimiter.write();
        }
    }

    return limiter*corr;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace fv

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
