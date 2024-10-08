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
    Test-fieldMapping

Description
    Test app for mapping of fields.

\*---------------------------------------------------------------------------*/

#include "global/argList/argList.H"
#include "fvMesh/fvMesh.H"
#include "fields/volFields/volFields.H"
#include "db/Time/TimeOpenFOAM.H"
#include "db/IOstreams/Fstreams/OFstream.H"
#include "meshTools/meshTools.H"
#include "polyTopoChange/polyTopoChange/removeFaces.H"
#include "meshes/polyMesh/mapPolyMesh/mapPolyMesh.H"
#include "polyTopoChange/polyTopoChange.H"
#include "cfdTools/general/include/fvCFD.H"
#include "primitives/random/Random/Random.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Main program:

int main(int argc, char *argv[])
{
    #include "include/addTimeOptions.H"
    argList::addArgument("inflate (true|false)");
    #include "include/setRootCase.H"
    #include "include/createTime.H"
    #include "include/createMesh.H"

    const Switch inflate(args[1]);

    if (inflate)
    {
        Info<< "Deleting cells using inflation/deflation" << nl << endl;
    }
    else
    {
        Info<< "Deleting cells, introducing points at new position" << nl
            << endl;
    }


    Random rndGen(0);



    // Test mapping
    // ------------
    // Mapping is volume averaged


    // 1. uniform field stays uniform
    volScalarField one
    (
        IOobject
        (
            "one",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedScalar("one", dimless, 1.0),
        fvPatchFieldBase::zeroGradientType()
    );
    Info<< "Writing one field "
        << one.name() << " in " << runTime.timeName() << endl;
    one.write();


    // 2. linear profile gets preserved
    volScalarField ccX
    (
        IOobject
        (
            "ccX",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh.C().component(0)
    );
    Info<< "Writing x component of cell centres to "
        << ccX.name()
        << " in " << runTime.timeName() << endl;
    ccX.write();


    // Uniform surface field
    surfaceScalarField surfaceOne
    (
        IOobject
        (
            "surfaceOne",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedScalar("one", dimless, 1.0)
    );
    Info<< "Writing surface one field "
        << surfaceOne.name() << " in " << runTime.timeName() << endl;
    surfaceOne.write();




    // Force allocation of V. Important for any mesh changes since otherwise
    // old time volumes are not stored
    const scalar totalVol = gSum(mesh.V());

    // Face removal engine. No checking for not merging boundary faces.
    removeFaces faceRemover(mesh, GREAT);

    // Comparison for inequality
    const auto isNotEqual = notEqualOp<scalar>(1e-10);

    while (runTime.loop())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

        if (!mesh.nInternalFaces())
        {
            break;
        }

        // Remove face
        label candidateFacei =
            rndGen.position<label>(0, mesh.nInternalFaces()-1);

        Info<< "Wanting to delete face " << mesh.faceCentres()[candidateFacei]
            << nl << endl;

        labelList candidates(1, candidateFacei);


        // Get compatible set of faces and connected sets of cells.
        labelList cellRegion;
        labelList cellRegionMaster;
        labelList facesToRemove;

        faceRemover.compatibleRemoves
        (
            candidates,
            cellRegion,
            cellRegionMaster,
            facesToRemove
        );

        // Topo changes container
        polyTopoChange meshMod(mesh);

        // Insert mesh refinement into polyTopoChange.
        faceRemover.setRefinement
        (
            facesToRemove,
            cellRegion,
            cellRegionMaster,
            meshMod
        );

        // Change mesh and inflate
        Info<< "Actually changing mesh" << nl << endl;
        autoPtr<mapPolyMesh> morphMap = meshMod.changeMesh(mesh, inflate);

        Info<< "Mapping fields" << nl << endl;
        mesh.updateMesh(morphMap());

        // Move mesh (since morphing does not do this)
        if (morphMap().hasMotionPoints())
        {
            Info<< "Moving mesh" << nl << endl;
            mesh.movePoints(morphMap().preMotionPoints());
        }

        // Update numbering of cells/vertices.
        faceRemover.updateMesh(morphMap());


        Info<< "Writing fields" << nl << endl;
        runTime.write();


        // Check mesh volume conservation
        if (mesh.moving())
        {
            #include "cfdTools/general/include/volContinuity.H"
        }
        else
        {
            if (mesh.V().size() != mesh.nCells())
            {
                FatalErrorInFunction
                    << "Volume not mapped. V:" << mesh.V().size()
                    << " nCells:" << mesh.nCells()
                    << exit(FatalError);
            }

            const scalar newVol = gSum(mesh.V());
            Info<< "Initial volume = " << totalVol
                << "  New volume = " << newVol
                << endl;

            if (mag(newVol-totalVol)/totalVol > 1e-10)
            {
                FatalErrorInFunction
                    << "Volume loss: old volume:" << totalVol
                    << "  new volume:" << newVol
                    << exit(FatalError);
            }
            else
            {
                Info<< "Volume check OK" << nl << endl;
            }
        }

        // Check constant profile
        {
            const scalar max = gMax(one);
            const scalar min = gMin(one);

            Info<< "Uniform one field min = " << min
                << "  max = " << max << endl;

            if (isNotEqual(max, 1) || isNotEqual(min, 1))
            {
                FatalErrorInFunction
                    << "Uniform volVectorField not preserved."
                    << " Min and max should both be 1.0. min:" << min
                    << " max:" << max
                    << exit(FatalError);
            }
            else
            {
                Info<< "Uniform field mapping check OK" << nl << endl;
            }
        }

        // Check linear profile
        {
            const scalarField diff = ccX-mesh.C().component(0);

            const scalar max = gMax(diff);
            const scalar min = gMin(diff);

            Info<< "Linear profile field min = " << min
                << "  max = " << max << endl;

            if (isNotEqual(max, 0) || isNotEqual(min, 0))
            {
                FatalErrorInFunction
                    << "Linear profile not preserved."
                    << " Min and max should both be 0.0. min:" << min
                    << " max:" << max
                    << exit(FatalError);
            }
            else
            {
                Info<< "Linear profile mapping check OK" << nl << endl;
            }
        }

        // Check face field mapping
        if (surfaceOne.size())
        {
            const scalar max = gMax(surfaceOne.primitiveField());
            const scalar min = gMin(surfaceOne.primitiveField());

            Info<< "Uniform surface field min = " << min
                << "  max = " << max << endl;

            if (isNotEqual(max, 1) || isNotEqual(min, 1))
            {
                FatalErrorInFunction
                    << "Uniform surfaceScalarField not preserved."
                    << " Min and max should both be 1.0. min:" << min
                    << " max:" << max
                    << exit(FatalError);
            }
            else
            {
                Info<< "Uniform surfaceScalarField mapping check OK" << nl
                    << endl;
            }
        }

        runTime.printExecutionTime(Info);
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
