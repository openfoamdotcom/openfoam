/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
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

Application
    kinematicParcelFoam

Group
    grpLagrangianSolvers

Description
    Transient solver for incompressible, turbulent flow with kinematic,
    particle cloud, and surface film modelling.

\*---------------------------------------------------------------------------*/

#include "cfdTools/general/include/fvCFD.H"
#include "dynamicFvMesh/dynamicFvMesh.H"
#include "singlePhaseTransportModel/singlePhaseTransportModel.H"
#include "turbulentTransportModels/turbulentTransportModel.H"
#include "surfaceFilmModel/surfaceFilmModel.H"
#include "clouds/derived/basicKinematicCloud/basicKinematicCloud.H"
#include "cfdTools/general/fvOptions/fvOptions.H"
#include "cfdTools/general/solutionControl/pimpleControl/pimpleControl.H"
#include "cfdTools/general/CorrectPhi/CorrectPhiPascal.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addNote
    (
        "Transient solver for incompressible, turbulent flow"
        " with kinematic particle clouds"
        " and surface film modelling."
    );

    #define CREATE_MESH createMeshesPostProcess.H
    #include "db/functionObjects/functionObjectList/postProcess.H"

    #include "include/addCheckCaseOptions.H"
    #include "include/setRootCaseLists.H"
    #include "include/createTime.H"
    #include "include/createDynamicFvMesh.H"
    #include "fluid/initContinuityErrs.H"
    #include "include/createDyMControls.H"
    #include "createFields.H"
    #include "createFieldRefs.H"
    #include "createRegionControls.H"
    #include "cfdTools/incompressible/createUfIfPresent.H"

    turbulence->validate();

    #include "cfdTools/incompressible/CourantNo.H"
    #include "cfdTools/general/include/setInitialDeltaT.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
        #include "include/readDyMControls.H"
        #include "cfdTools/incompressible/CourantNo.H"
        #include "include/setMultiRegionDeltaT.H"

        ++runTime;

        Info<< "Time = " << runTime.timeName() << nl << endl;

        // Store the particle positions
        parcels.storeGlobalPositions();

        // Do any mesh changes
        mesh.update();

        if (solvePrimaryRegion && mesh.changing())
        {
            MRF.update();

            if (correctPhi)
            {
                // Calculate absolute flux
                // from the mapped surface velocity
                phi = mesh.Sf() & Uf();

                #include "../../incompressible/pimpleFoam/correctPhi.H"

                // Make the fluxes relative to the mesh-motion
                fvc::makeRelative(phi, U);
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
            // --- PIMPLE loop
            while (pimple.loop())
            {
                #include "fluid/UEqn.H"

                // --- Pressure corrector loop
                while (pimple.correct())
                {
                    #include "fluid/pEqn.H"
                }

                if (pimple.turbCorr())
                {
                    laminarTransport.correct();
                    turbulence->correct();
                }
            }
        }

        runTime.write();

        runTime.printExecutionTime(Info);
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
