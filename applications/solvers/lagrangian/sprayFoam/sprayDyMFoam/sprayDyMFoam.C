/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2015-2017 OpenFOAM Foundation
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
    sprayDyMFoam

Group
    grpLagrangianSolvers grpMovingMeshSolvers

Description
    Transient solver for compressible, turbulent flow with a spray particle
    cloud, with optional mesh motion and mesh topology changes.

\*---------------------------------------------------------------------------*/

#include "cfdTools/general/include/fvCFD.H"
#include "dynamicFvMesh/dynamicFvMesh.H"
#include "turbulenceModel.H"
#include "clouds/derived/basicSprayCloud/basicSprayCloud.H"
#include "psiReactionThermo/psiReactionThermo.H"
#include "CombustionModel.H"
#include "radiationModels/radiationModel/radiationModel.H"
#include "SLGThermo/SLGThermo.H"
#include "cfdTools/general/solutionControl/pimpleControl/pimpleControl.H"
#include "cfdTools/general/CorrectPhi/CorrectPhiPascal.H"
#include "cfdTools/general/fvOptions/fvOptions.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addNote
    (
        "Transient solver for compressible, turbulent flow"
        " with a spray particle cloud.\n"
        "With optional mesh motion and mesh topology changes.\n"
    );

    #include "db/functionObjects/functionObjectList/postProcess.H"

    #include "include/setRootCaseLists.H"
    #include "include/createTime.H"
    #include "include/createDynamicFvMesh.H"
    #include "include/createDyMControls.H"
    #include "createFields.H"
    #include "createFieldRefs.H"
    #include "cfdTools/compressible/createRhoUf.H"
    #include "fluid/compressibleCourantNo.H"
    #include "cfdTools/general/include/setInitialDeltaT.H"
    #include "fluid/initContinuityErrs.H"

    turbulence->validate();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
        #include "include/readDyMControls.H"

        {
            // Store divrhoU from the previous time-step/mesh for the correctPhi
            volScalarField divrhoU
            (
                "divrhoU",
                fvc::div(fvc::absolute(phi, rho, U))
            );

            #include "fluid/compressibleCourantNo.H"
            #include "cfdTools/general/include/setDeltaT.H"

            ++runTime;

            Info<< "Time = " << runTime.timeName() << nl << endl;

            // Store momentum to set rhoUf for introduced faces.
            volVectorField rhoU("rhoU", rho*U);

            // Store the particle positions
            parcels.storeGlobalPositions();

            // Do any mesh changes
            mesh.update();

            if (mesh.changing())
            {
                MRF.update();

                if (correctPhi)
                {
                    // Calculate absolute flux from the mapped surface velocity
                    phi = mesh.Sf() & rhoUf;

                    #include "correctPhi.H"

                    // Make the fluxes relative to the mesh-motion
                    fvc::makeRelative(phi, rho, U);
                }

                if (checkMeshCourantNo)
                {
                    #include "include/meshCourantNo.H"
                }
            }
        }

        parcels.evolve();

        #include "cfdTools/compressible/rhoEqn.H"

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
            #include "fluid/UEqn.H"
            #include "fluid/YEqn.H"
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

        if (runTime.write())
        {
            combustion->Qdot()().write();
        }

        runTime.printExecutionTime(Info);
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
