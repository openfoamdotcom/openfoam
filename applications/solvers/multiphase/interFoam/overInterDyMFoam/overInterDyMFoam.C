/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2014 OpenFOAM Foundation
    Copyright (C) 2016-2021 OpenCFD Ltd.
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
    overInterDyMFoam

Group
    grpMultiphaseSolvers grpMovingMeshSolvers

Description
    Solver for two incompressible, isothermal immiscible fluids using a VOF
    (volume of fluid) phase-fraction based interface capturing approach,
    with optional mesh motion and mesh topology changes including adaptive
    re-meshing.

\*---------------------------------------------------------------------------*/

#include "cfdTools/general/include/fvCFD.H"
#include "dynamicFvMesh/dynamicFvMesh.H"
#include "fvMatrices/solvers/MULES/CMULES.H"
#include "finiteVolume/ddtSchemes/EulerDdtScheme/EulerDdtScheme.H"
#include "finiteVolume/ddtSchemes/localEulerDdtScheme/localEulerDdtScheme.H"
#include "finiteVolume/ddtSchemes/CrankNicolsonDdtScheme/CrankNicolsonDdtScheme.H"
#include "algorithms/subCycle/subCycle.H"
#include "immiscibleIncompressibleTwoPhaseMixture.H"
#include "turbulentTransportModels/turbulentTransportModel.H"
#include "cfdTools/general/solutionControl/pimpleControl/pimpleControl.H"
#include "cfdTools/general/fvOptions/fvOptions.H"
#include "finiteVolume/fvc/fvcSmooth/fvcSmooth.H"
#include "cellCellStencil/cellCellStencil/cellCellStencilObject.H"
#include "interpolation/surfaceInterpolation/schemes/localMin/localMin.H"
#include "oversetAdjustPhi/oversetAdjustPhi.H"
#include "oversetPatchPhiErr/oversetPatchPhiErr.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addNote
    (
        "Solver for two incompressible, isothermal immiscible fluids using"
        " VOF phase-fraction based interface capturing\n"
        "With optional mesh motion and mesh topology changes including"
        " adaptive re-meshing."
    );

    #include "db/functionObjects/functionObjectList/postProcess.H"

    #include "include/setRootCaseLists.H"
    #include "include/createTime.H"
    #include "include/createDynamicFvMesh.H"
    #include "fluid/initContinuityErrs.H"

    #include "include/createDyMControls.H"
    #include "createFields.H"
    #include "solvers/multiphase/VoF/createAlphaFluxes.H"
    #include "cfdTools/general/include/createFvOptions.H"

    volScalarField rAU
    (
        IOobject
        (
            "rAU",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedScalar("rAUf", dimTime/rho.dimensions(), 1.0)
    );

    #include "cfdTools/incompressible/createUf.H"
    #include "include/createControls.H"

    #include "include/setCellMask.H"
    #include "include/setInterpolatedCells.H"

    turbulence->validate();

    if (!LTS)
    {
        #include "cfdTools/incompressible/CourantNo.H"
        #include "cfdTools/general/include/setInitialDeltaT.H"
    }

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    Info<< "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
        #include "include/readDyMControls.H"
        #include "include/readOversetDyMControls.H"

        if (LTS)
        {
            #include "solvers/multiphase/VoF/setRDeltaT.H"
        }
        else
        {
            #include "cfdTools/incompressible/CourantNo.H"
            #include "solvers/multiphase/VoF/alphaCourantNo.H"
            #include "cfdTools/general/include/setDeltaT.H"
        }

        ++runTime;

        Info<< "Time = " << runTime.timeName() << nl << endl;

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
            if (pimple.firstIter() || moveMeshOuterCorrectors)
            {
                scalar timeBeforeMeshUpdate = runTime.elapsedCpuTime();

                mesh.update();

                if (mesh.changing())
                {
                    Info<< "Execution time for mesh.update() = "
                        << runTime.elapsedCpuTime() - timeBeforeMeshUpdate
                        << " s" << endl;

                    // Do not apply previous time-step mesh compression flux
                    // if the mesh topology changed
                    if (mesh.topoChanging())
                    {
                        talphaPhi1Corr0.clear();
                    }

                    // Update cellMask field for blocking out hole cells
                    #include "include/setCellMask.H"
                    #include "include/setInterpolatedCells.H"
                    #include "include/correctPhiFaceMask.H"

                    gh = (g & mesh.C()) - ghRef;
                    ghf = (g & mesh.Cf()) - ghRef;


                    mixture.correct();

                    // Make the flux relative to the mesh motion
                    fvc::makeRelative(phi, U);

                }

                if (mesh.changing() && checkMeshCourantNo)
                {
                    #include "include/meshCourantNo.H"
                }
            }

            if (adjustFringe)
            {
                oversetAdjustPhi(phi, U, zoneIdMass);
            }

            #include "cfdTools/general/include/alphaControls.H"
            #include "solvers/multiphase/VoF/alphaEqnSubCycle.H"

            rhoPhi *= faceMask;

            mixture.correct();

            #include "fluid/UEqn.H"

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

        runTime.write();

        runTime.printExecutionTime(Info);
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
