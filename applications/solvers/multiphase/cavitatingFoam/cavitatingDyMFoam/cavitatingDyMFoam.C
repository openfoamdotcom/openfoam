/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2012-2017 OpenFOAM Foundation
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
    cavitatingFoam

Group
    grpMultiphaseSolvers grpMovingMeshSolvers

Description
    Transient cavitation solver based on the homogeneous equilibrium model
    from which the compressibility of the liquid/vapour 'mixture' is obtained,
    with optional mesh motion and mesh topology changes.

    Turbulence modelling is generic, i.e. laminar, RAS or LES may be selected.

\*---------------------------------------------------------------------------*/

#include "cfdTools/general/include/fvCFD.H"
#include "dynamicFvMesh/dynamicFvMesh.H"
#include "barotropicCompressibilityModel/barotropicCompressibilityModel.H"
#include "incompressibleTwoPhaseMixture/incompressibleTwoPhaseMixture.H"
#include "turbulentTransportModels/turbulentTransportModel.H"
#include "cfdTools/general/CorrectPhi/CorrectPhiPascal.H"
#include "cfdTools/general/solutionControl/pimpleControl/pimpleControl.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addNote
    (
        "Transient cavitation solver based on the homogeneous equilibrium"
        " model from which the compressibility of the liquid/vapour 'mixture'"
        " is obtained.\n"
        "With optional mesh motion and mesh topology changes."
    );

    #include "db/functionObjects/functionObjectList/postProcess.H"

    #include "include/setRootCaseLists.H"
    #include "include/createTime.H"
    #include "include/createDynamicFvMesh.H"
    #include "include/createControls.H"
    #include "createFields.H"
    #include "cfdTools/incompressible/createUf.H"
    #include "createPcorrTypes.H"
    #include "cfdTools/incompressible/CourantNo.H"
    #include "cfdTools/general/include/setInitialDeltaT.H"

    turbulence->validate();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
        #include "readControls.H"

        {
            #include "cfdTools/incompressible/CourantNo.H"
            #include "cfdTools/general/include/setDeltaT.H"

            ++runTime;

            Info<< "Time = " << runTime.timeName() << nl << endl;

            // Do any mesh changes
            mesh.update();

            if (mesh.changing() && correctPhi)
            {
                // Calculate absolute flux from the mapped surface velocity
                phi = mesh.Sf() & Uf;

                #include "correctPhi.H"

                // Make the flux relative to the mesh motion
                fvc::makeRelative(phi, U);
            }
        }

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
            #include "cfdTools/compressible/rhoEqn.H"
            #include "alphavPsi.H"
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
