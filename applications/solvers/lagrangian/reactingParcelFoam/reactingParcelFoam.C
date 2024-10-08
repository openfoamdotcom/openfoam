/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2020 OpenFOAM Foundation
    Copyright (C) 2018-2020 OpenCFD Ltd.
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
    reactingParcelFoam

Group
    grpLagrangianSolvers

Description
    Transient solver for compressible, turbulent flow with a reacting,
    multiphase particle cloud, and surface film modelling.

\*---------------------------------------------------------------------------*/

#include "cfdTools/general/include/fvCFD.H"
#include "dynamicFvMesh/dynamicFvMesh.H"
#include "turbulentFluidThermoModels/turbulentFluidThermoModel.H"
#include "surfaceFilmModel/surfaceFilmModel.H"
#include "rhoReactionThermo/rhoReactionThermo.H"
#include "CombustionModel.H"
#include "radiationModels/radiationModel/radiationModel.H"
#include "SLGThermo/SLGThermo.H"
#include "cfdTools/general/fvOptions/fvOptions.H"
#include "cfdTools/general/solutionControl/pimpleControl/pimpleControl.H"
#include "cfdTools/general/pressureControl/pressureControl.H"
#include "cfdTools/general/CorrectPhi/CorrectPhiPascal.H"
#include "finiteVolume/ddtSchemes/localEulerDdtScheme/localEulerDdtScheme.H"
#include "finiteVolume/fvc/fvcSmooth/fvcSmooth.H"
#include "include/cloudMacros.H"

#ifndef CLOUD_BASE_TYPE
    #define CLOUD_BASE_TYPE ReactingMultiphase
    #define CLOUD_BASE_TYPE_NAME "reacting"
#endif

#include CLOUD_INCLUDE_FILE(CLOUD_BASE_TYPE)
#define basicReactingTypeCloud CLOUD_TYPE(CLOUD_BASE_TYPE)

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addNote
    (
        "Transient solver for compressible, turbulent flow"
        " with reacting, multiphase particle clouds"
        " and surface film modelling."
    );

    #define CREATE_MESH createMeshesPostProcess.H
    #include "db/functionObjects/functionObjectList/postProcess.H"

    #include "include/addCheckCaseOptions.H"
    #include "include/setRootCaseLists.H"
    #include "include/createTime.H"
    #include "include/createDynamicFvMesh.H"
    #include "include/createDyMControls.H"
    #include "createFields.H"
    #include "createFieldRefs.H"
    #include "createRegionControls.H"
    #include "fluid/initContinuityErrs.H"
    #include "cfdTools/compressible/createRhoUfIfPresent.H"

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

        // Store divrhoU from the previous mesh
        // so that it can be mapped and used in correctPhi
        // to ensure the corrected phi has the same divergence
        autoPtr<volScalarField> divrhoU;
        if (solvePrimaryRegion && correctPhi)
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
            #include "include/setMultiRegionDeltaT.H"
        }

        ++runTime;

        Info<< "Time = " << runTime.timeName() << nl << endl;

        // Store momentum to set rhoUf for introduced faces.
        autoPtr<volVectorField> rhoU;
        if (solvePrimaryRegion && rhoUf.valid())
        {
            rhoU.reset(new volVectorField("rhoU", rho*U));
        }

        // Store the particle positions
        parcels.storeGlobalPositions();

        // Do any mesh changes
        mesh.update();

        if (solvePrimaryRegion && mesh.changing())
        {
            gh = (g & mesh.C()) - ghRef;
            ghf = (g & mesh.Cf()) - ghRef;

            MRF.update();

            if (correctPhi)
            {
                // Calculate absolute flux
                // from the mapped surface velocity
                phi = mesh.Sf() & rhoUf();

                #include "../../compressible/rhoPimpleFoam/correctPhi.H"

                // Make the fluxes relative to the mesh-motion
                fvc::makeRelative(phi, rho, U);
            }

            if (checkMeshCourantNo)
            {
                #include "include/meshCourantNo.H"
            }
        }

        parcels.evolve();
        surfaceFilm.evolve();

        if (solvePrimaryRegion)
        {
            if (pimple.nCorrPIMPLE() <= 1)
            {
                #include "cfdTools/compressible/rhoEqn.H"
            }

            // --- PIMPLE loop
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
        }

        runTime.write();

        runTime.printExecutionTime(Info);
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
