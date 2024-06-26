/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2019 OpenCFD Ltd.
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

#include "matrices/lduMatrix/solvers/GAMG/interfaces/GAMGInterface/GAMGInterface.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(GAMGInterface, 0);
    defineRunTimeSelectionTable(GAMGInterface, lduInterface);
    defineRunTimeSelectionTable(GAMGInterface, Istream);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::GAMGInterface::GAMGInterface
(
    const label index,
    const lduInterfacePtrsList& coarseInterfaces,
    Istream& is
)
:
    index_(index),
    coarseInterfaces_(coarseInterfaces),
    faceCells_(is),
    faceRestrictAddressing_(is)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::GAMGInterface::combine(const GAMGInterface& coarseGi)
{
    const labelList& coarseFra = coarseGi.faceRestrictAddressing_;

    forAll(faceRestrictAddressing_, ffi)
    {
        faceRestrictAddressing_[ffi] = coarseFra[faceRestrictAddressing_[ffi]];
    }

    faceCells_ = coarseGi.faceCells_;
}


Foam::tmp<Foam::labelField> Foam::GAMGInterface::interfaceInternalField
(
    const labelUList& internalData
) const
{
    return interfaceInternalField<label>(internalData);
}


Foam::tmp<Foam::labelField> Foam::GAMGInterface::interfaceInternalField
(
    const labelUList& internalData,
    const labelUList& faceCells
) const
{
    return interfaceInternalField<label>(internalData, faceCells);
}


Foam::tmp<Foam::scalarField> Foam::GAMGInterface::agglomerateCoeffs
(
    const scalarField& fineCoeffs
) const
{
    auto tcoarseCoeffs = tmp<scalarField>::New(size(), Zero);
    auto& coarseCoeffs = tcoarseCoeffs.ref();

    if (fineCoeffs.size() != faceRestrictAddressing_.size())
    {
        FatalErrorInFunction
            << "Size of coefficients " << fineCoeffs.size()
            << " does not correspond to the size of the restriction "
            << faceRestrictAddressing_.size()
            << abort(FatalError);
    }
    if (debug && max(faceRestrictAddressing_) > size())
    {
        FatalErrorInFunction
            << "Face restrict addressing addresses outside of coarse interface"
            << " size. Max addressing:" << max(faceRestrictAddressing_)
            << " coarse size:" << size()
            << abort(FatalError);
    }

    forAll(faceRestrictAddressing_, ffi)
    {
        coarseCoeffs[faceRestrictAddressing_[ffi]] += fineCoeffs[ffi];
    }

    return tcoarseCoeffs;
}


void Foam::GAMGInterface::write(Ostream& os) const
{
    os  << faceCells_ << token::SPACE << faceRestrictAddressing_;
}


// ************************************************************************* //
