/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2013-2016 OpenFOAM Foundation
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
    thermoFoam

Group
    grpHeatTransferSolvers

Description
    Solver for energy transport and thermodynamics on a frozen flow field.

\*---------------------------------------------------------------------------*/

#include "cfdTools/general/include/fvCFD.H"
#include "rhoThermo/rhoThermo.H"
#include "turbulentFluidThermoModels/turbulentFluidThermoModel.H"
#include "LES/LESModel/LESModel.H"
#include "radiationModels/radiationModel/radiationModel.H"
#include "cfdTools/general/fvOptions/fvOptions.H"
#include "cfdTools/general/solutionControl/simpleControl/simpleControl.H"
#include "cfdTools/general/solutionControl/pimpleControl/pimpleControl.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addNote
    (
        "Solver for energy transport and thermodynamics on a frozen flow field"
    );

    #define NO_CONTROL
    #include "db/functionObjects/functionObjectList/postProcess.H"

    #include "include/addCheckCaseOptions.H"
    #include "include/setRootCaseLists.H"
    #include "include/createTime.H"
    #include "include/createMesh.H"
    #include "createFields.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nEvolving thermodynamics\n" << endl;

    if (mesh.solutionDict().found("SIMPLE"))
    {
        simpleControl simple(mesh);

        while (simple.loop())
        {
            Info<< "Time = " << runTime.timeName() << nl << endl;

            while (simple.correctNonOrthogonal())
            {
                #include "fluid/EEqn.H"
            }

            runTime.write();

            runTime.printExecutionTime(Info);
        }
    }
    else
    {
        pimpleControl pimple(mesh);

        while (runTime.run())
        {
            ++runTime;

            Info<< "Time = " << runTime.timeName() << nl << endl;

            while (pimple.correctNonOrthogonal())
            {
                #include "fluid/EEqn.H"
            }

            runTime.write();

            runTime.printExecutionTime(Info);
        }
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
