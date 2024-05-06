/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2017-2019,2022 OpenCFD Ltd.
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
    chtMultiRegionSimpleFoam

Group
    grpHeatTransferSolvers

Description
    Steady-state solver for buoyant, turbulent fluid flow and solid heat
    conduction with conjugate heat transfer between solid and fluid regions.

\*---------------------------------------------------------------------------*/

#include "cfdTools/general/include/fvCFD.H"
#include "rhoThermo/rhoThermo.H"
#include "turbulentFluidThermoModels/turbulentFluidThermoModel.H"
#include "fields/fvPatchFields/basic/fixedGradient/fixedGradientFvPatchFields.H"
#include "regionModel/regionProperties/regionProperties.H"
#include "solidThermo/solidThermo.H"
#include "radiationModels/radiationModel/radiationModel.H"
#include "cfdTools/general/fvOptions/fvOptions.H"
#include "primitives/coordinate/systems/coordinateSystem.H"
#include "cfdTools/general/solutionControl/loopControl/loopControl.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addNote
    (
        "Steady-state solver for buoyant, turbulent fluid flow and solid heat"
        " conduction with conjugate heat transfer"
        " between solid and fluid regions."
    );

    #define NO_CONTROL
    #define CREATE_MESH createMeshesPostProcess.H
    #include "db/functionObjects/functionObjectList/postProcess.H"

    #include "include/addCheckCaseOptions.H"
    #include "include/setRootCaseLists.H"
    #include "include/createTime.H"
    #include "createMeshes.H"
    #include "createFields.H"
    #include "include/createCoupledRegions.H"
    #include "fluid/initContinuityErrs.H"

    while (runTime.loop())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

        forAll(fluidRegions, i)
        {
            fvMesh& mesh = fluidRegions[i];

            Info<< "\nSolving for fluid region "
                << fluidRegions[i].name() << endl;
            #include "fluid/readFluidMultiRegionSIMPLEControls.H"
            #include "fluid/setRegionFluidFields.H"
            #include "fluid/solveFluid.H"
        }

        forAll(solidRegions, i)
        {
            fvMesh& mesh = solidRegions[i];

            #include "solid/readSolidMultiRegionSIMPLEControls.H"
            #include "solid/setRegionSolidFields.H"
            #include "solid/solveSolid.H"
        }


        if (coupled)
        {
            Info<< "\nSolving energy coupled regions" << endl;
            fvMatrixAssemblyPtr->solve();
            #include "include/correctThermos.H"

            forAll(fluidRegions, i)
            {
                fvMesh& mesh = fluidRegions[i];

                #include "solid/readSolidMultiRegionSIMPLEControls.H"
                #include "fluid/setRegionFluidFields.H"
                if (!frozenFlow)
                {
                    #include "fluid/pEqn.H"
                    turb.correct();
                }
            }

            fvMatrixAssemblyPtr->clear();
        }

        // Additional loops for energy solution only
        {
            loopControl looping(runTime, "SIMPLE", "energyCoupling");

            while (looping.loop())
            {
                Info<< nl << looping << nl;

                forAll(fluidRegions, i)
                {
                    fvMesh& mesh = fluidRegions[i];

                    Info<< "\nSolving for fluid region "
                        << fluidRegions[i].name() << endl;
                    #include "fluid/readFluidMultiRegionSIMPLEControls.H"
                    #include "fluid/setRegionFluidFields.H"
                    frozenFlow = true;
                    #include "fluid/solveFluid.H"
                }

                forAll(solidRegions, i)
                {
                    fvMesh& mesh = solidRegions[i];

                    Info<< "\nSolving for solid region "
                        << solidRegions[i].name() << endl;
                    #include "solid/readSolidMultiRegionSIMPLEControls.H"
                    #include "solid/setRegionSolidFields.H"
                    #include "solid/solveSolid.H"
                }

                if (coupled)
                {
                    Info<< "\nSolving energy coupled regions.. " << endl;
                    fvMatrixAssemblyPtr->solve();
                    #include "include/correctThermos.H"

                    fvMatrixAssemblyPtr->clear();
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
