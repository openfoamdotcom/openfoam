/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2013-2019 OpenFOAM Foundation
    Copyright (C) 2020-2022 OpenCFD Ltd.
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

#include "multiphaseSystem/reactingEuler_multiphaseSystem.H"
#include "derivedFvPatchFields/alphaContactAngle/alphaContactAngleFvPatchScalarField.H"

#include "fvMatrices/solvers/MULES/MULES.H"
#include "algorithms/subCycle/subCycle.H"
#include "fields/Fields/UniformField/UniformField.H"

#include "finiteVolume/fvc/fvcDdt.H"
#include "finiteVolume/fvc/fvcDiv.H"
#include "finiteVolume/fvc/fvcSnGrad.H"
#include "finiteVolume/fvc/fvcFlux.H"
#include "finiteVolume/fvc/fvcMeshPhi.H"
#include "finiteVolume/fvc/fvcSup.H"

#include "finiteVolume/fvm/fvmDdt.H"
#include "finiteVolume/fvm/fvmLaplacian.H"
#include "finiteVolume/fvm/fvmSup.H"

#include "global/constants/unitConversion.H"

// * * * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(multiphaseSystem, 0);
    defineRunTimeSelectionTable(multiphaseSystem, dictionary);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::multiphaseSystem::calcAlphas()
{
    scalar level = 0.0;
    alphas_ == 0.0;

    forAll(phases(), i)
    {
        alphas_ += level*phases()[i];
        level += 1.0;
    }
}


void Foam::multiphaseSystem::solveAlphas()
{
    forAll(phases(), phasei)
    {
        phases()[phasei].correctBoundaryConditions();
    }

    // Calculate the void fraction
    volScalarField alphaVoid
    (
        IOobject
        (
            "alphaVoid",
            mesh_.time().timeName(),
            mesh_
        ),
        mesh_,
        dimensionedScalar("1", dimless, 1)
    );
    forAll(stationaryPhases(), stationaryPhasei)
    {
        alphaVoid -= stationaryPhases()[stationaryPhasei];
    }

    // Generate face-alphas
    PtrList<surfaceScalarField> alphafs(phases().size());
    forAll(phases(), phasei)
    {
        phaseModel& phase = phases()[phasei];
        alphafs.set
        (
            phasei,
            new surfaceScalarField
            (
                IOobject::groupName("alphaf", phase.name()),
                upwind<scalar>(mesh_, phi_).interpolate(phase)
            )
        );
    }

    // Create correction fluxes
    PtrList<surfaceScalarField> alphaPhiCorrs(phases().size());
    forAll(stationaryPhases(), stationaryPhasei)
    {
        phaseModel& phase = stationaryPhases()[stationaryPhasei];

        alphaPhiCorrs.set
        (
            phase.index(),
            new surfaceScalarField
            (
                IOobject::groupName("alphaPhiCorr", phase.name()),
              - upwind<scalar>(mesh_, phi_).flux(phase)
            )
        );
    }
    forAll(movingPhases(), movingPhasei)
    {
        phaseModel& phase = movingPhases()[movingPhasei];
        volScalarField& alpha = phase;

        alphaPhiCorrs.set
        (
            phase.index(),
            new surfaceScalarField
            (
                IOobject::groupName("alphaPhiCorr", phase.name()),
                fvc::flux(phi_, phase, "div(phi," + alpha.name() + ')')
            )
        );

        surfaceScalarField& alphaPhiCorr = alphaPhiCorrs[phase.index()];

        forAll(phases(), phasei)
        {
            phaseModel& phase2 = phases()[phasei];
            volScalarField& alpha2 = phase2;

            if (&phase2 == &phase) continue;

            surfaceScalarField phir(phase.phi() - phase2.phi());

            cAlphaTable::const_iterator cAlpha
            (
                cAlphas_.find(phasePairKey(phase.name(), phase2.name()))
            );

            if (cAlpha != cAlphas_.end())
            {
                surfaceScalarField phic
                (
                    (mag(phi_) + mag(phir))/mesh_.magSf()
                );

                phir += min(cAlpha()*phic, max(phic))*nHatf(phase, phase2);
            }

            word phirScheme
            (
                "div(phir," + alpha2.name() + ',' + alpha.name() + ')'
            );

            alphaPhiCorr += fvc::flux
            (
                -fvc::flux(-phir, phase2, phirScheme),
                phase,
                phirScheme
            );
        }

        phase.correctInflowOutflow(alphaPhiCorr);

        MULES::limit
        (
            geometricOneField(),
            phase,
            phi_,
            alphaPhiCorr,
            zeroField(),
            zeroField(),
            min(alphaVoid.primitiveField(), phase.alphaMax())(),
            zeroField(),
            true
        );
    }

    // Limit the flux sums, fixing those of the stationary phases
    labelHashSet fixedAlphaPhiCorrs;
    forAll(stationaryPhases(), stationaryPhasei)
    {
        fixedAlphaPhiCorrs.insert(stationaryPhases()[stationaryPhasei].index());
    }
    MULES::limitSum(alphafs, alphaPhiCorrs, fixedAlphaPhiCorrs);

    // Solve for the moving phase alphas
    forAll(movingPhases(), movingPhasei)
    {
        phaseModel& phase = movingPhases()[movingPhasei];
        volScalarField& alpha = phase;

        surfaceScalarField& alphaPhi = alphaPhiCorrs[phase.index()];
        alphaPhi += upwind<scalar>(mesh_, phi_).flux(phase);
        phase.correctInflowOutflow(alphaPhi);

        volScalarField::Internal Sp
        (
            IOobject
            (
                "Sp",
                mesh_.time().timeName(),
                mesh_
            ),
            mesh_,
            dimensionedScalar(dimless/dimTime, Zero)
        );

        volScalarField::Internal Su
        (
            "Su",
            min(alpha, scalar(1))*fvc::div(fvc::absolute(phi_, phase.U()))
        );

        if (phase.divU().valid())
        {
            const scalarField& dgdt = phase.divU()();

            forAll(dgdt, celli)
            {
                if (dgdt[celli] > 0.0)
                {
                    Sp[celli] -= dgdt[celli];
                    Su[celli] += dgdt[celli];
                }
                else if (dgdt[celli] < 0.0)
                {
                    Sp[celli] +=
                        dgdt[celli]
                       *(1 - alpha[celli])/max(alpha[celli], 1e-4);
                }
            }
        }

        forAll(phases(), phasej)
        {
            const phaseModel& phase2 = phases()[phasej];
            const volScalarField& alpha2 = phase2;

            if (&phase2 == &phase) continue;

            if (phase2.divU().valid())
            {
                const scalarField& dgdt2 = phase2.divU()();

                forAll(dgdt2, celli)
                {
                    if (dgdt2[celli] < 0.0)
                    {
                        Sp[celli] +=
                            dgdt2[celli]
                           *(1 - alpha2[celli])/max(alpha2[celli], 1e-4);

                        Su[celli] -=
                            dgdt2[celli]
                           *alpha[celli]/max(alpha2[celli], 1e-4);
                    }
                    else if (dgdt2[celli] > 0.0)
                    {
                        Sp[celli] -= dgdt2[celli];
                    }
                }
            }
        }

        MULES::explicitSolve
        (
            geometricOneField(),
            alpha,
            alphaPhi,
            Sp,
            Su
        );

        phase.alphaPhiRef() = alphaPhi;
    }

    // Report the phase fractions and the phase fraction sum
    forAll(phases(), phasei)
    {
        phaseModel& phase = phases()[phasei];

        Info<< phase.name() << " fraction, min, max = "
            << phase.weightedAverage(mesh_.V()).value()
            << ' ' << min(phase).value()
            << ' ' << max(phase).value()
            << endl;
    }

    volScalarField sumAlphaMoving
    (
        IOobject
        (
            "sumAlphaMoving",
            mesh_.time().timeName(),
            mesh_
        ),
        mesh_,
        dimensionedScalar(dimless, Zero)
    );
    forAll(movingPhases(), movingPhasei)
    {
        sumAlphaMoving += movingPhases()[movingPhasei];
    }

    Info<< "Phase-sum volume fraction, min, max = "
        << (sumAlphaMoving + 1 - alphaVoid)().weightedAverage(mesh_.V()).value()
        << ' ' << min(sumAlphaMoving + 1 - alphaVoid).value()
        << ' ' << max(sumAlphaMoving + 1 - alphaVoid).value()
        << endl;

    // Correct the sum of the phase fractions to avoid drift
    forAll(movingPhases(), movingPhasei)
    {
        movingPhases()[movingPhasei] *= alphaVoid/sumAlphaMoving;
    }
}


Foam::tmp<Foam::surfaceVectorField> Foam::multiphaseSystem::nHatfv
(
    const volScalarField& alpha1,
    const volScalarField& alpha2
) const
{
    /*
    // Cell gradient of alpha
    volVectorField gradAlpha =
        alpha2*fvc::grad(alpha1) - alpha1*fvc::grad(alpha2);

    // Interpolated face-gradient of alpha
    surfaceVectorField gradAlphaf = fvc::interpolate(gradAlpha);
    */

    surfaceVectorField gradAlphaf
    (
        fvc::interpolate(alpha2)*fvc::interpolate(fvc::grad(alpha1))
      - fvc::interpolate(alpha1)*fvc::interpolate(fvc::grad(alpha2))
    );

    // Face unit interface normal
    return gradAlphaf/(mag(gradAlphaf) + deltaN_);
}


Foam::tmp<Foam::surfaceScalarField> Foam::multiphaseSystem::nHatf
(
    const volScalarField& alpha1,
    const volScalarField& alpha2
) const
{
    // Face unit interface normal flux
    return nHatfv(alpha1, alpha2) & mesh_.Sf();
}


// Correction for the boundary condition on the unit normal nHat on
// walls to produce the correct contact angle.

// The dynamic contact angle is calculated from the component of the
// velocity on the direction of the interface, parallel to the wall.

void Foam::multiphaseSystem::correctContactAngle
(
    const phaseModel& phase1,
    const phaseModel& phase2,
    surfaceVectorField::Boundary& nHatb
) const
{
    const volScalarField::Boundary& gbf
        = phase1.boundaryField();

    const fvBoundaryMesh& boundary = mesh_.boundary();

    forAll(boundary, patchi)
    {
        if
        (
            isA<reactingMultiphaseEuler::alphaContactAngleFvPatchScalarField>
            (
                gbf[patchi]
            )
        )
        {
            const auto& acap =
                refCast
                <
                    const reactingMultiphaseEuler::
                        alphaContactAngleFvPatchScalarField
                >(gbf[patchi]);

            vectorField& nHatPatch = nHatb[patchi];

            vectorField AfHatPatch
            (
                mesh_.Sf().boundaryField()[patchi]
               /mesh_.magSf().boundaryField()[patchi]
            );

            reactingMultiphaseEuler::alphaContactAngleFvPatchScalarField::
                thetaPropsTable::const_iterator tp =
                    acap.thetaProps()
                   .find(phasePairKey(phase1.name(), phase2.name()));

            if (tp == acap.thetaProps().end())
            {
                FatalErrorInFunction
                    << "Cannot find interface "
                    << phasePairKey(phase1.name(), phase2.name())
                    << "\n    in table of theta properties for patch "
                    << acap.patch().name()
                    << exit(FatalError);
            }

            bool matched = (tp.key().first() == phase1.name());

            scalar theta0 = degToRad(tp().theta0(matched));
            scalarField theta(boundary[patchi].size(), theta0);

            scalar uTheta = tp().uTheta();

            // Calculate the dynamic contact angle if required
            if (uTheta > SMALL)
            {
                const scalar thetaA = degToRad(tp().thetaA(matched));
                const scalar thetaR = degToRad(tp().thetaR(matched));

                // Calculated the component of the velocity parallel to the wall
                vectorField Uwall
                (
                    phase1.U()().boundaryField()[patchi].patchInternalField()
                  - phase1.U()().boundaryField()[patchi]
                );
                Uwall -= (AfHatPatch & Uwall)*AfHatPatch;

                // Find the direction of the interface parallel to the wall
                vectorField nWall
                (
                    nHatPatch - (AfHatPatch & nHatPatch)*AfHatPatch
                );

                // Normalise nWall
                nWall /= (mag(nWall) + SMALL);

                // Calculate Uwall resolved normal to the interface parallel to
                // the interface
                scalarField uwall(nWall & Uwall);

                theta += (thetaA - thetaR)*tanh(uwall/uTheta);
            }


            // Reset nHatPatch to correspond to the contact angle

            scalarField a12(nHatPatch & AfHatPatch);

            scalarField b1(cos(theta));

            scalarField b2(nHatPatch.size());

            forAll(b2, facei)
            {
                b2[facei] = cos(acos(a12[facei]) - theta[facei]);
            }

            scalarField det(1 - a12*a12);

            scalarField a((b1 - a12*b2)/det);
            scalarField b((b2 - a12*b1)/det);

            nHatPatch = a*AfHatPatch + b*nHatPatch;

            nHatPatch /= (mag(nHatPatch) + deltaN_.value());
        }
    }
}


Foam::tmp<Foam::volScalarField> Foam::multiphaseSystem::K
(
    const phaseModel& phase1,
    const phaseModel& phase2
) const
{
    tmp<surfaceVectorField> tnHatfv = nHatfv(phase1, phase2);

    correctContactAngle(phase1, phase2, tnHatfv.ref().boundaryFieldRef());

    // Simple expression for curvature
    return -fvc::div(tnHatfv & mesh_.Sf());
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::multiphaseSystem::multiphaseSystem
(
    const fvMesh& mesh
)
:
    phaseSystem(mesh),

    alphas_
    (
        IOobject
        (
            "alphas",
            mesh_.time().timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedScalar(dimless, Zero)
    ),

    cAlphas_(lookup("interfaceCompression")),

    deltaN_
    (
        "deltaN",
        1e-8/pow(average(mesh_.V()), 1.0/3.0)
    )
{
    forAll(phases(), phasei)
    {
        volScalarField& alphai = phases()[phasei];
        mesh_.setFluxRequired(alphai.name());
    }
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Foam::tmp<Foam::surfaceScalarField> Foam::multiphaseSystem::surfaceTension
(
    const phaseModel& phase1
) const
{
    tmp<surfaceScalarField> tSurfaceTension
    (
        surfaceScalarField::New
        (
            "surfaceTension",
            mesh_,
            dimensionedScalar(dimensionSet(1, -2, -2, 0, 0), Zero)
        )
    );

    tSurfaceTension.ref().setOriented();

    forAll(phases(), phasej)
    {
        const phaseModel& phase2 = phases()[phasej];

        if (&phase2 != &phase1)
        {
            phasePairKey key12(phase1.name(), phase2.name());

            cAlphaTable::const_iterator cAlpha(cAlphas_.find(key12));

            if (cAlpha != cAlphas_.end())
            {
                tSurfaceTension.ref() +=
                    fvc::interpolate(sigma(key12)*K(phase1, phase2))
                   *(
                        fvc::interpolate(phase2)*fvc::snGrad(phase1)
                      - fvc::interpolate(phase1)*fvc::snGrad(phase2)
                    );
            }
        }
    }

    tSurfaceTension->setOriented();

    return tSurfaceTension;
}


Foam::tmp<Foam::volScalarField>
Foam::multiphaseSystem::nearInterface() const
{
    tmp<volScalarField> tnearInt
    (
        volScalarField::New
        (
            "nearInterface",
            mesh_,
            dimensionedScalar(dimless, Zero)
        )
    );

    forAll(phases(), phasei)
    {
        tnearInt.ref() = max
        (
            tnearInt(),
            pos0(phases()[phasei] - 0.01)*pos0(0.99 - phases()[phasei])
        );
    }

    return tnearInt;
}


void Foam::multiphaseSystem::solve()
{
    const Time& runTime = mesh_.time();

    const dictionary& alphaControls = mesh_.solverDict("alpha");
    label nAlphaSubCycles(alphaControls.get<label>("nAlphaSubCycles"));

    bool LTS = fv::localEulerDdt::enabled(mesh_);

    if (nAlphaSubCycles > 1)
    {
        tmp<volScalarField> trSubDeltaT;

        if (LTS)
        {
            trSubDeltaT =
                fv::localEulerDdt::localRSubDeltaT(mesh_, nAlphaSubCycles);
        }

        List<volScalarField*> alphaPtrs(phases().size());
        PtrList<surfaceScalarField> alphaPhiSums(phases().size());

        forAll(phases(), phasei)
        {
            phaseModel& phase = phases()[phasei];
            volScalarField& alpha = phase;

            alphaPtrs[phasei] = &alpha;

            alphaPhiSums.set
            (
                phasei,
                new surfaceScalarField
                (
                    IOobject
                    (
                        "phiSum" + alpha.name(),
                        runTime.timeName(),
                        mesh_
                    ),
                    mesh_,
                    dimensionedScalar(dimensionSet(0, 3, -1, 0, 0), Zero)
                )
            );
        }

        for
        (
            subCycleTime alphaSubCycle
            (
                const_cast<Time&>(runTime),
                nAlphaSubCycles
            );
            !(++alphaSubCycle).end();
        )
        {
            solveAlphas();

            forAll(phases(), phasei)
            {
                alphaPhiSums[phasei] += phases()[phasei].alphaPhi();
            }
        }

        forAll(phases(), phasei)
        {
            phaseModel& phase = phases()[phasei];
            if (phase.stationary()) continue;

            phase.alphaPhiRef() = alphaPhiSums[phasei]/nAlphaSubCycles;
        }
    }
    else
    {
        solveAlphas();
    }

    forAll(phases(), phasei)
    {
        phaseModel& phase = phases()[phasei];
        if (phase.stationary()) continue;

        phase.alphaRhoPhiRef() =
            fvc::interpolate(phase.rho())*phase.alphaPhi();

        phase.clamp_range(SMALL, 1 - SMALL);
    }

    calcAlphas();
}


// ************************************************************************* //
