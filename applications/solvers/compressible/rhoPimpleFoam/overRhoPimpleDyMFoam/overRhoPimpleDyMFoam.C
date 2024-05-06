/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2015 OpenFOAM Foundation
    Copyright (C) 2016-2022 OpenCFD Ltd.
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

Application
    overRhoPimpleDyMFoam

Group
    grpCompressibleSolvers grpMovingMeshSolvers

Description
    Transient solver for laminar or turbulent flow of compressible fluids
    for HVAC and similar applications.

    Uses the flexible PIMPLE (PISO-SIMPLE) solution for time-resolved and
    pseudo-transient simulations.

\*---------------------------------------------------------------------------*/

#include "cfdTools/general/include/fvCFD.H"
#include "dynamicFvMesh/dynamicFvMesh.H"
#include "fluidThermo/fluidThermo.H"
#include "turbulentFluidThermoModels/turbulentFluidThermoModel.H"
#include "cfdTools/general/solutionControl/pimpleControl/pimpleControl.H"
#include "cfdTools/general/pressureControl/pressureControl.H"
#include "cfdTools/general/CorrectPhi/CorrectPhiPascal.H"
#include "cfdTools/general/fvOptions/fvOptions.H"
#include "finiteVolume/ddtSchemes/localEulerDdtScheme/localEulerDdtScheme.H"
#include "finiteVolume/fvc/fvcSmooth/fvcSmooth.H"
#include "cellCellStencil/cellCellStencil/cellCellStencilObject.H"
#include "interpolation/surfaceInterpolation/schemes/localMin/localMin.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addNote
    (
        "Transient solver for compressible turbulent flow.\n"
        "With optional mesh motion and mesh topology changes."
    );

    #include "include/setRootCaseLists.H"
    #include "include/createTime.H"
    #include "include/createDynamicFvMesh.H"
    #include "include/createDyMControls.H"
    #include "cfdTools/general/include/createRDeltaT.H"
    #include "fluid/initContinuityErrs.H"
    #include "createFields.H"
    #include "cfdTools/general/include/createMRF.H"
    #include "cfdTools/general/include/createFvOptions.H"
    #include "cfdTools/compressible/createRhoUfIfPresent.H"
    #include "include/createControls.H"

    turbulence->validate();

    if (!LTS)
    {
        #include "fluid/compressibleCourantNo.H"
        #include "cfdTools/general/include/setInitialDeltaT.H"
    }

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
        #include "include/readDyMControls.H"

        // Store divrhoU from the previous mesh so that it can be mapped
        // and used in correctPhi to ensure the corrected phi has the
        // same divergence
        autoPtr<volScalarField> divrhoU;
        if (correctPhi)
        {
            divrhoU.reset
            (
                new volScalarField
                (
                    "divrhoU",
                    fvc::div(fvc::absolute(phi, rho, U))
                )
            );
        }

        if (LTS)
        {
            #include "solvers/multiphase/VoF/setRDeltaT.H"
        }
        else
        {
            #include "fluid/compressibleCourantNo.H"
            #include "cfdTools/general/include/setDeltaT.H"
        }

        ++runTime;

        Info<< "Time = " << runTime.timeName() << nl << endl;

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
            if (pimple.firstIter() || moveMeshOuterCorrectors)
            {
                // Do any mesh changes
                mesh.update();

                if (mesh.changing())
                {
                    MRF.update();

                    #include "include/setCellMask.H"
                    #include "include/setInterpolatedCells.H"
                    #include "include/correctRhoPhiFaceMask.H"

                    if (correctPhi)
                    {
                        // Corrects flux on separated regions
                        #include "correctPhi.H"
                    }

                     // Make the fluxes relative to the mesh-motion
                    fvc::makeRelative(phi, rho, U);

                    if (checkMeshCourantNo)
                    {
                        #include "include/meshCourantNo.H"
                    }
                }
            }

            if (pimple.firstIter() && !pimple.SIMPLErho())
            {
                #include "cfdTools/compressible/rhoEqn.H"
            }

            #include "fluid/UEqn.H"
            #include "fluid/EEqn.H"

            // --- Pressure corrector loop
            while (pimple.correct())
            {
                #include "fluid/pEqn.H"
            }

            if (pimple.turbCorr())
            {
                turbulence->correct();
            }
        }

        rho = thermo.rho();

        runTime.write();

        runTime.printExecutionTime(Info);
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
