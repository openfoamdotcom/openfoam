/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
    Copyright (C) 2019-2020 OpenCFD Ltd.
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

#include "pairPotential/pairPotentialList/pairPotentialList.H"
#include "db/IOstreams/Fstreams/OFstream.H"
#include "db/Time/TimeOpenFOAM.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::pairPotentialList::readPairPotentialDict
(
    const List<word>& idList,
    const dictionary& pairPotentialDict,
    const polyMesh& mesh
)
{
    Info<< nl << "Building pair potentials." << endl;

    rCutMax_ = 0.0;

    for (label a = 0; a < nIds_; ++a)
    {
        word idA = idList[a];

        for (label b = a; b < nIds_; ++b)
        {
            word idB = idList[b];

            word pairPotentialName;

            if (a == b)
            {
                if (pairPotentialDict.found(idA + "-" + idB))
                {
                    pairPotentialName = idA + "-" + idB;
                }
                else
                {
                    FatalErrorInFunction
                        << "Pair pairPotential specification subDict "
                        << idA << "-" << idB << " not found"
                        << nl << abort(FatalError);
                }
            }
            else
            {
                if (pairPotentialDict.found(idA + "-" + idB))
                {
                    pairPotentialName = idA + "-" + idB;
                }

                else if (pairPotentialDict.found(idB + "-" + idA))
                {
                    pairPotentialName = idB + "-" + idA;
                }

                else
                {
                    FatalErrorInFunction
                        << "Pair pairPotential specification subDict "
                        << idA << "-" << idB << " or "
                        << idB << "-" << idA << " not found"
                        << nl << abort(FatalError);
                }

                if
                (
                    pairPotentialDict.found(idA+"-"+idB)
                 && pairPotentialDict.found(idB+"-"+idA)
                )
                {
                    FatalErrorInFunction
                        << "Pair pairPotential specification subDict "
                        << idA << "-" << idB << " and "
                        << idB << "-" << idA << " found multiple definition"
                        << nl << abort(FatalError);
                }
            }

            (*this).set
            (
                pairPotentialIndex(a, b),
                pairPotential::New
                (
                    pairPotentialName,
                    pairPotentialDict.subDict(pairPotentialName)
                )
            );

            if ((*this)[pairPotentialIndex(a, b)].rCut() > rCutMax_)
            {
                rCutMax_ = (*this)[pairPotentialIndex(a, b)].rCut();
            }

            if ((*this)[pairPotentialIndex(a, b)].writeTables())
            {
                fileHandler().mkDir(mesh.time().path());
                autoPtr<OSstream> ppTabFile
                (
                    fileHandler().NewOFstream
                    (
                        mesh.time().path()/pairPotentialName
                    )
                );

                if
                (
                    !(*this)[pairPotentialIndex(a, b)].writeEnergyAndForceTables
                    (
                        ppTabFile()
                    )
                )
                {
                    FatalErrorInFunction
                        << "Failed writing to "
                        << ppTabFile().name() << nl
                        << abort(FatalError);
                }
            }
        }
    }

    if (!pairPotentialDict.found("electrostatic"))
    {
        FatalErrorInFunction
            << "Pair pairPotential specification subDict electrostatic"
            << nl << abort(FatalError);
    }

    electrostaticPotential_ = pairPotential::New
    (
        "electrostatic",
        pairPotentialDict.subDict("electrostatic")
    );

    if (electrostaticPotential_->rCut() > rCutMax_)
    {
        rCutMax_ = electrostaticPotential_->rCut();
    }

    if (electrostaticPotential_->writeTables())
    {
        fileHandler().mkDir(mesh.time().path());
        autoPtr<OSstream> ppTabFile
        (
            fileHandler().NewOFstream
            (
                mesh.time().path()/"electrostatic"
            )
        );

        if (!electrostaticPotential_->writeEnergyAndForceTables(ppTabFile()))
        {
            FatalErrorInFunction
                << "Failed writing to "
                << ppTabFile().name() << nl
                << abort(FatalError);
        }
    }

    rCutMaxSqr_ = rCutMax_*rCutMax_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::pairPotentialList::pairPotentialList()
:
    PtrList<pairPotential>()
{}


Foam::pairPotentialList::pairPotentialList
(
    const List<word>& idList,
    const dictionary& pairPotentialDict,
    const polyMesh& mesh
)
:
    PtrList<pairPotential>()
{
    buildPotentials(idList, pairPotentialDict, mesh);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::pairPotentialList::~pairPotentialList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::pairPotentialList::buildPotentials
(
    const List<word>& idList,
    const dictionary& pairPotentialDict,
    const polyMesh& mesh
)
{
    setSize(((idList.size()*(idList.size() + 1))/2));

    nIds_ = idList.size();

    readPairPotentialDict(idList, pairPotentialDict, mesh);
}


const Foam::pairPotential& Foam::pairPotentialList::pairPotentialFunction
(
    const label a,
    const label b
) const
{
    return (*this)[pairPotentialIndex(a, b)];
}


bool Foam::pairPotentialList::rCutMaxSqr(const scalar rIJMagSqr) const
{
    if (rIJMagSqr < rCutMaxSqr_)
    {
        return true;
    }

    return false;
}


bool Foam::pairPotentialList::rCutSqr
(
    const label a,
    const label b,
    const scalar rIJMagSqr
) const
{
    if (rIJMagSqr < rCutSqr(a, b))
    {
        return true;
    }

    return false;
}


Foam::scalar Foam::pairPotentialList::rMin
(
    const label a,
    const label b
) const
{
    return (*this)[pairPotentialIndex(a, b)].rMin();
}


Foam::scalar Foam::pairPotentialList::dr
(
    const label a,
    const label b
) const
{
    return (*this)[pairPotentialIndex(a, b)].dr();
}


Foam::scalar Foam::pairPotentialList::rCutSqr
(
    const label a,
    const label b
) const
{
    return (*this)[pairPotentialIndex(a, b)].rCutSqr();
}


Foam::scalar Foam::pairPotentialList::rCut
(
    const label a,
    const label b
) const
{
    return (*this)[pairPotentialIndex(a, b)].rCut();
}


Foam::scalar Foam::pairPotentialList::force
(
    const label a,
    const label b,
    const scalar rIJMag
) const
{
    scalar f = (*this)[pairPotentialIndex(a, b)].force(rIJMag);

    return f;
}


Foam::scalar Foam::pairPotentialList::energy
(
    const label a,
    const label b,
    const scalar rIJMag
) const
{
    scalar e = (*this)[pairPotentialIndex(a, b)].energy(rIJMag);

    return e;
}


// ************************************************************************* //
