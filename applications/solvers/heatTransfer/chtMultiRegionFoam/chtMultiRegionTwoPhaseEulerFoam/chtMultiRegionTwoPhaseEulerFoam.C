/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2018-2022 OpenCFD Ltd.
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
    chtMultiRegionTwoPhaseEulerFoam

Group
    grpHeatTransferSolvers

Description
    Transient solver for buoyant, turbulent fluid flow and solid heat
    conduction with conjugate heat transfer between solid and fluid regions.

    It solves a two-phase Euler approach on the fluid region.

\*---------------------------------------------------------------------------*/

#include "cfdTools/general/include/fvCFD.H"
#include "turbulentFluidThermoModels/turbulentFluidThermoModel.H"

#include "twoPhaseSystem/twoPhaseSystem.H"
#include "turbulence/phaseCompressibleTurbulenceModel.H"
#include "cfdTools/general/solutionControl/pimpleControl/pimpleControl.H"
#include "fields/fvPatchFields/basic/fixedGradient/fixedGradientFvPatchFields.H"
#include "regionModel/regionProperties/regionProperties.H"
#include "solid/solidRegionDiffNo.H"
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
        "Transient solver for buoyant, turbulent two phase fluid flow and"
        "solid heat conduction with conjugate heat transfer "
        "between solid and fluid regions."
    );

    #define NO_CONTROL
    #define CREATE_MESH createMeshesPostProcess.H
    #include "db/functionObjects/functionObjectList/postProcess.H"

    #include "include/addCheckCaseOptions.H"
    #include "include/setRootCase.H"
    #include "include/createTime.H"
    #include "createMeshes.H"
    #include "createFields.H"
    #include "fluid/initContinuityErrs.H"
    #include "cfdTools/general/include/createTimeControls.H"
    #include "solid/readSolidTimeControls.H"
    #include "fluid/compressibleMultiRegionCourantNo.H"
    #include "solid/solidRegionDiffusionNo.H"
    #include "include/setInitialMultiRegionDeltaT.H"

    while (runTime.run())
    {
        #include "cfdTools/general/include/readTimeControls.H"
        #include "solid/readSolidTimeControls.H"
        #include "readPIMPLEControls.H"

        #include "fluid/compressibleMultiRegionCourantNo.H"
        #include "solid/solidRegionDiffusionNo.H"
        #include "include/setMultiRegionDeltaT.H"

        ++runTime;

        Info<< "Time = " << runTime.timeName() << nl << endl;

        if (nOuterCorr != 1)
        {
            forAll(fluidRegions, i)
            {
                #include "fluid/storeOldFluidFields.H"
            }
        }

        // --- PIMPLE loop
        for (int oCorr=0; oCorr<nOuterCorr; ++oCorr)
        {
            const bool finalIter = (oCorr == nOuterCorr-1);

            forAll(fluidRegions, i)
            {
                fvMesh& mesh = fluidRegions[i];

                Info<< "\nSolving for fluid region "
                    << fluidRegions[i].name() << endl;
                #include "fluid/readFluidMultiRegionPIMPLEControls.H"
                #include "fluid/setRegionFluidFields.H"
                #include "fluid/solveFluid.H"
            }

            forAll(solidRegions, i)
            {
                fvMesh& mesh = solidRegions[i];

                Info<< "\nSolving for solid region "
                    << solidRegions[i].name() << endl;
                #include "solid/readSolidMultiRegionPIMPLEControls.H"
                #include "solid/setRegionSolidFields.H"
                #include "solid/solveSolid.H"
            }

            // Additional loops for energy solution only
            if (!oCorr && nOuterCorr > 1)
            {
                loopControl looping(runTime, pimple, "energyCoupling");

                while (looping.loop())
                {
                    Info<< nl << looping << nl;

                    forAll(fluidRegions, i)
                    {
                        fvMesh& mesh = fluidRegions[i];

                        Info<< "\nSolving for fluid region "
                            << fluidRegions[i].name() << endl;
                        #include "fluid/readFluidMultiRegionPIMPLEControls.H"
                        #include "fluid/setRegionFluidFields.H"
                        frozenFlow = true;
                        #include "fluid/solveFluid.H"
                    }

                    forAll(solidRegions, i)
                    {
                        fvMesh& mesh = solidRegions[i];

                        Info<< "\nSolving for solid region "
                            << solidRegions[i].name() << endl;
                        #include "solid/readSolidMultiRegionPIMPLEControls.H"
                        #include "solid/setRegionSolidFields.H"
                        #include "solid/solveSolid.H"
                    }
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
