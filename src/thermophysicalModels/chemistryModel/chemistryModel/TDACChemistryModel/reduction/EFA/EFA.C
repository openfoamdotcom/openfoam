/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016 OpenFOAM Foundation
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

#include "chemistryModel/TDACChemistryModel/reduction/EFA/EFA.H"
#include "chemistryModel/TDACChemistryModel/reduction/EFA/SortableListEFA.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CompType, class ThermoType>
Foam::chemistryReductionMethods::EFA<CompType, ThermoType>::EFA
(
    const IOdictionary& dict,
    TDACChemistryModel<CompType, ThermoType>& chemistry
)
:
    chemistryReductionMethod<CompType, ThermoType>(dict, chemistry),
    sC_(this->nSpecie_, Zero),
    sH_(this->nSpecie_, Zero),
    sO_(this->nSpecie_, Zero),
    sN_(this->nSpecie_, Zero),
    sortPart_(0.05)
{
    const List<List<specieElement>>& specieComposition =
    this->chemistry_.specieComp();
    for (label i=0; i<this->nSpecie_; i++)
    {
        const List<specieElement>& curSpecieComposition =
        specieComposition[i];
        // for all elements in the current species
        forAll(curSpecieComposition, j)
        {
            const specieElement& curElement =
            curSpecieComposition[j];
            if (curElement.name() == "C")
            {
                sC_[i] = curElement.nAtoms();
            }
            else if (curElement.name() == "H")
            {
                sH_[i] = curElement.nAtoms();
            }
            else if (curElement.name() == "O")
            {
                sO_[i] = curElement.nAtoms();
            }
            else if (curElement.name() == "N")
            {
                sN_[i] = curElement.nAtoms();
            }
            else
            {
                Info<< "element not considered"<< endl;
            }
        }
    }

    this->coeffsDict_.readIfPresent("sortPart", sortPart_);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CompType, class ThermoType>
Foam::chemistryReductionMethods::EFA<CompType, ThermoType>::~EFA()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CompType, class ThermoType>
void Foam::chemistryReductionMethods::EFA<CompType, ThermoType>::reduceMechanism
(
    const scalarField &c,
    const scalar T,
    const scalar p
)
{
    scalarField& completeC(this->chemistry_.completeC());
    scalarField c1(this->chemistry_.nEqns(), Zero);

    for (label i=0; i<this->nSpecie_; i++)
    {
        c1[i] = c[i];
        completeC[i] = c[i];
    }

    c1[this->nSpecie_] = T;
    c1[this->nSpecie_+1] = p;


    // Number of initialized rAB for each lines
    Field<label> NbrABInit(this->nSpecie_, Zero);

    // Position of the initialized rAB, -1 when not initialized
    RectangularMatrix<label> rABPos(this->nSpecie_, this->nSpecie_, -1);
    RectangularMatrix<scalar> CFluxAB(this->nSpecie_, this->nSpecie_, Zero);
    RectangularMatrix<scalar> HFluxAB(this->nSpecie_, this->nSpecie_, Zero);
    RectangularMatrix<scalar> OFluxAB(this->nSpecie_, this->nSpecie_, Zero);
    RectangularMatrix<scalar> NFluxAB(this->nSpecie_, this->nSpecie_, Zero);
    scalar CFlux(0.0), HFlux(0.0), OFlux(0.0), NFlux(0.0);
    label nbPairs(0);

    // Index of the other species involved in the rABNum
    RectangularMatrix<label> rABOtherSpec(this->nSpecie_, this->nSpecie_, -1);

    scalar pf, cf, pr, cr;
    label lRef, rRef;
    forAll(this->chemistry_.reactions(), i)
    {
        const Reaction<ThermoType>& R = this->chemistry_.reactions()[i];
        // for each reaction compute omegai
        this->chemistry_.omega
        (
            R, c1, T, p, pf, cf, lRef, pr, cr, rRef
        );
        scalar fr = mag(pf*cf)+mag(pr*cr);
        scalar NCi(0.0),NHi(0.0),NOi(0.0),NNi(0.0);
        forAll(R.lhs(),s)
        {
            label curIndex = R.lhs()[s].index;
            scalar stoicCoeff = R.lhs()[s].stoichCoeff;
            NCi += sC_[curIndex]*stoicCoeff;
            NHi += sH_[curIndex]*stoicCoeff;
            NOi += sO_[curIndex]*stoicCoeff;
            NNi += sN_[curIndex]*stoicCoeff;
        }
        // element conservation means that total number of element is
        // twice the number on the left
        NCi *=2;
        NHi *=2;
        NOi *=2;
        NNi *=2;
        // then for each source/sink pairs, compute the element flux
        forAll(R.lhs(), Ai)// compute the element flux
        {
            label A = R.lhs()[Ai].index;
            scalar Acoeff = R.lhs()[Ai].stoichCoeff;

            forAll(R.rhs(), Bi)
            {
                label B = R.rhs()[Bi].index;
                scalar Bcoeff = R.rhs()[Bi].stoichCoeff;
                // if a pair in the reversed way has not been initialized
                if (rABPos(B, A)==-1)
                {
                    label otherS = rABPos(A, B);
                    if (otherS==-1)
                    {
                        rABPos(A, B) = NbrABInit[A]++;
                        otherS = rABPos(A, B);
                        nbPairs++;
                        rABOtherSpec(A, otherS) = B;
                    }
                    if (NCi>VSMALL)
                    {
                        CFluxAB(A, otherS) +=
                            fr*Acoeff*sC_[A]*Bcoeff*sC_[B]/NCi;
                    }
                    if (NHi>VSMALL)
                    {
                        HFluxAB(A, otherS) +=
                            fr*Acoeff*sH_[A]*Bcoeff*sH_[B]/NHi;
                    }
                    if (NOi>VSMALL)
                    {
                        OFluxAB(A, otherS) +=
                            fr*Acoeff*sO_[A]*Bcoeff*sO_[B]/NOi;
                    }
                    if (NNi>VSMALL)
                    {
                        NFluxAB(A, otherS) +=
                            fr*Acoeff*sN_[A]*Bcoeff*sN_[B]/NNi;
                    }
                }
                // If a pair BA is initialized,
                // add the element flux to this pair
                else
                {
                    label otherS = rABPos(B, A);
                    if (NCi>VSMALL)
                    {
                        CFluxAB(B, otherS) +=
                            fr*Acoeff*sC_[A]*Bcoeff*sC_[B]/NCi;
                    }
                    if (NHi>VSMALL)
                    {
                        HFluxAB(B, otherS) +=
                            fr*Acoeff*sH_[A]*Bcoeff*sH_[B]/NHi;
                    }
                    if (NOi>VSMALL)
                    {
                        OFluxAB(B, otherS) +=
                            fr*Acoeff*sO_[A]*Bcoeff*sO_[B]/NOi;
                    }
                    if (NNi>VSMALL)
                    {
                        NFluxAB(B, otherS) +=
                            fr*Acoeff*sN_[A]*Bcoeff*sN_[B]/NNi;
                    }
                }
                if (NCi>VSMALL)
                {
                    CFlux += fr*Acoeff*sC_[A]*Bcoeff*sC_[B]/NCi;
                }
                if (NHi>VSMALL)
                {
                    HFlux += fr*Acoeff*sH_[A]*Bcoeff*sH_[B]/NHi;
                }
                if (NOi>VSMALL)
                {
                    OFlux += fr*Acoeff*sO_[A]*Bcoeff*sO_[B]/NOi;
                }
                if (NNi>VSMALL)
                {
                    NFlux += fr*Acoeff*sN_[A]*Bcoeff*sN_[B]/NNi;
                }
            }
        }
    }

    // Select species according to the total flux cutoff (1-tolerance)
    // of the flux is included
    label speciesNumber = 0;
    for (label i=0; i<this->nSpecie_; i++)
    {
        this->activeSpecies_[i] = false;
    }

    if (CFlux > VSMALL)
    {
        SortableListEFA<scalar> pairsFlux(nbPairs);
        labelList source(nbPairs);
        labelList sink(nbPairs);
        label nP(0);
        for (int A=0; A<this->nSpecie_ ; A++)
        {
            for (int j=0; j<NbrABInit[A]; j++)
            {
                label pairIndex = nP++;
                pairsFlux[pairIndex] = 0.0;
                label B = rABOtherSpec(A, j);
                pairsFlux[pairIndex] += CFluxAB(A, j);
                source[pairIndex] = A;
                sink[pairIndex] = B;
            }
        }

        // Sort in descending orders the source/sink pairs until the cutoff is
        // reached. The sorting is done on part of the pairs because a small
        // part of these pairs are responsible for a large part of the element
        // flux
        scalar cumFlux(0.0);
        scalar threshold((1-this->tolerance())*CFlux);
        label startPoint(0);
        label nbToSort(static_cast<label> (nbPairs*sortPart_));
        nbToSort = max(nbToSort,1);

        bool cumRespected(false);
        while(!cumRespected)
        {
            if (startPoint >= nbPairs)
            {
                FatalErrorInFunction
                    << "startPoint outside number of pairs without reaching"
                    << "100% flux"
                    << exit(FatalError);
            }

            label nbi = min(nbToSort, nbPairs-startPoint);
            pairsFlux.partialSort(nbi, startPoint);
            const labelList& idx = pairsFlux.indices();
            for (int i=0; i<nbi; i++)
            {
                cumFlux += pairsFlux[idx[startPoint+i]];
                if (!this->activeSpecies_[source[idx[startPoint+i]]])
                {
                    this->activeSpecies_[source[idx[startPoint+i]]] = true;
                    speciesNumber++;
                }
                if (!this->activeSpecies_[sink[idx[startPoint+i]]])
                {
                    this->activeSpecies_[sink[idx[startPoint+i]]] = true;
                    speciesNumber++;
                }
                if (cumFlux >= threshold)
                {
                    cumRespected = true;
                    break;
                }
            }
            startPoint += nbToSort;
        }
    }

    if (HFlux > VSMALL)
    {
        SortableListEFA<scalar> pairsFlux(nbPairs);
        labelList source(nbPairs);
        labelList sink(nbPairs);
        label nP(0);
        for (int A=0; A<this->nSpecie_ ; A++)
        {
            for (int j=0; j<NbrABInit[A]; j++)
            {
                label pairIndex = nP++;
                pairsFlux[pairIndex] = 0.0;
                label B = rABOtherSpec(A, j);
                pairsFlux[pairIndex] += HFluxAB(A, j);
                source[pairIndex] = A;
                sink[pairIndex] = B;
            }
        }

        scalar cumFlux(0.0);
        scalar threshold((1-this->tolerance())*HFlux);
        label startPoint(0);
        label nbToSort(static_cast<label> (nbPairs*sortPart_));
        nbToSort = max(nbToSort,1);

        bool cumRespected(false);
        while(!cumRespected)
        {
            if (startPoint >= nbPairs)
            {
                FatalErrorInFunction
                    << "startPoint outside number of pairs without reaching"
                    << "100% flux"
                    << exit(FatalError);
            }

            label nbi = min(nbToSort, nbPairs-startPoint);
            pairsFlux.partialSort(nbi, startPoint);
            const labelList& idx = pairsFlux.indices();
            for (int i=0; i<nbi; i++)
            {
                cumFlux += pairsFlux[idx[startPoint+i]];

                if (!this->activeSpecies_[source[idx[startPoint+i]]])
                {
                    this->activeSpecies_[source[idx[startPoint+i]]] = true;
                    speciesNumber++;
                }
                if (!this->activeSpecies_[sink[idx[startPoint+i]]])
                {
                    this->activeSpecies_[sink[idx[startPoint+i]]] = true;
                    speciesNumber++;
                }
                if (cumFlux >= threshold)
                {
                    cumRespected = true;
                    break;
                }
            }
            startPoint += nbToSort;
        }
    }

    if (OFlux > VSMALL)
    {
        SortableListEFA<scalar> pairsFlux(nbPairs);
        labelList source(nbPairs);
        labelList sink(nbPairs);
        label nP(0);
        for (int A=0; A<this->nSpecie_ ; A++)
        {
            for (int j=0; j<NbrABInit[A]; j++)
            {
                label pairIndex = nP++;
                pairsFlux[pairIndex] = 0.0;
                label B = rABOtherSpec(A, j);
                pairsFlux[pairIndex] += OFluxAB(A, j);
                source[pairIndex] = A;
                sink[pairIndex] = B;
            }
        }
        scalar cumFlux(0.0);
        scalar threshold((1-this->tolerance())*OFlux);
        label startPoint(0);
        label nbToSort(static_cast<label> (nbPairs*sortPart_));
        nbToSort = max(nbToSort,1);

        bool cumRespected(false);
        while(!cumRespected)
        {
            if (startPoint >= nbPairs)
            {
                FatalErrorInFunction
                    << "startPoint outside number of pairs without reaching"
                    << "100% flux"
                    << exit(FatalError);
            }

            label nbi = min(nbToSort, nbPairs-startPoint);
            pairsFlux.partialSort(nbi, startPoint);
            const labelList& idx = pairsFlux.indices();
            for (int i=0; i<nbi; i++)
            {
                cumFlux += pairsFlux[idx[startPoint+i]];

                if (!this->activeSpecies_[source[idx[startPoint+i]]])
                {
                    this->activeSpecies_[source[idx[startPoint+i]]] = true;
                    speciesNumber++;
                }
                if (!this->activeSpecies_[sink[idx[startPoint+i]]])
                {
                    this->activeSpecies_[sink[idx[startPoint+i]]] = true;
                    speciesNumber++;
                }
                if (cumFlux >= threshold)
                {
                    cumRespected = true;
                    break;
                }
            }
            startPoint += nbToSort;
        }
    }

    if (NFlux > VSMALL)
    {
        SortableListEFA<scalar> pairsFlux(nbPairs);
        labelList source(nbPairs);
        labelList sink(nbPairs);
        label nP(0);
        for (int A=0; A<this->nSpecie_ ; A++)
        {
            for (int j=0; j<NbrABInit[A]; j++)
            {
                label pairIndex = nP++;
                pairsFlux[pairIndex] = 0.0;
                label B = rABOtherSpec(A, j);
                pairsFlux[pairIndex] += NFluxAB(A, j);
                source[pairIndex] = A;
                sink[pairIndex] = B;
            }
        }
        scalar cumFlux(0.0);
        scalar threshold((1-this->tolerance())*NFlux);
        label startPoint(0);
        label nbToSort(static_cast<label> (nbPairs*sortPart_));
        nbToSort = max(nbToSort,1);

        bool cumRespected(false);
        while(!cumRespected)
        {
            if (startPoint >= nbPairs)
            {
                FatalErrorInFunction
                    << "startPoint outside number of pairs without reaching"
                    << "100% flux"
                    << exit(FatalError);
            }

            label nbi = min(nbToSort, nbPairs-startPoint);
            pairsFlux.partialSort(nbi, startPoint);
            const labelList& idx = pairsFlux.indices();
            for (int i=0; i<nbi; i++)
            {
                cumFlux += pairsFlux[idx[startPoint+i]];

                if (!this->activeSpecies_[source[idx[startPoint+i]]])
                {
                    this->activeSpecies_[source[idx[startPoint+i]]] = true;
                    speciesNumber++;
                }
                if (!this->activeSpecies_[sink[idx[startPoint+i]]])
                {
                    this->activeSpecies_[sink[idx[startPoint+i]]] = true;
                    speciesNumber++;
                }
                if (cumFlux >= threshold)
                {
                    cumRespected = true;
                    break;
                }
            }
            startPoint += nbToSort;
        }
    }

    // Put a flag on the reactions containing at least one removed species
    forAll(this->chemistry_.reactions(), i)
    {
        const Reaction<ThermoType>& R = this->chemistry_.reactions()[i];
        this->chemistry_.reactionsDisabled()[i] = false;
        forAll(R.lhs(), s)
        {
            label ss = R.lhs()[s].index;
            if (!this->activeSpecies_[ss])
            {
                this->chemistry_.reactionsDisabled()[i] = true;
                break;
            }
        }
        if (!this->chemistry_.reactionsDisabled()[i])
        {
            forAll(R.rhs(), s)
            {
                label ss = R.rhs()[s].index;
                if (!this->activeSpecies_[ss])
                {
                    this->chemistry_.reactionsDisabled()[i] = true;
                    break;
                }
            }
        }
    }

    this->NsSimp_ = speciesNumber;
    scalarField& simplifiedC(this->chemistry_.simplifiedC());
    simplifiedC.setSize(this->NsSimp_+2);
    DynamicList<label>& s2c(this->chemistry_.simplifiedToCompleteIndex());
    s2c.setSize(this->NsSimp_);
    Field<label>& c2s(this->chemistry_.completeToSimplifiedIndex());
    label j = 0;

    for (label i=0; i<this->nSpecie_; i++)
    {
        if (this->activeSpecies_[i])
        {
            s2c[j] = i;
            simplifiedC[j] = c[i];
            c2s[i] = j++;
            if (!this->chemistry_.active(i))
            {
                this->chemistry_.setActive(i);
            }
        }
        else
        {
            c2s[i] = -1;
        }
    }
    simplifiedC[this->NsSimp_] = T;
    simplifiedC[this->NsSimp_+1] = p;
    this->chemistry_.setNsDAC(this->NsSimp_);
    // change temporary Ns in chemistryModel
    // to make the function nEqns working
    this->chemistry_.setNSpecie(this->NsSimp_);
}


// ************************************************************************* //
