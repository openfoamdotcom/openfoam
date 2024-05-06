/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
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
    testMappedPatch

Description
    Test mapped b.c. by mapping face centres (mesh.C().boundaryField()).

\*---------------------------------------------------------------------------*/


#include "global/argList/argList.H"
#include "fvMesh/fvMesh.H"
#include "fields/volFields/volFields.H"
#include "meshTools/meshTools.H"
#include "db/Time/TimeOpenFOAM.H"
#include "db/IOstreams/Fstreams/OFstream.H"
#include "mappedPatches/mappedPolyPatch/mappedPolyPatch.H"
#include "fields/fvPatchFields/derived/mappedFixedValue/mappedFixedValueFvPatchFields.H"
#include "cfdTools/general/include/fvCFD.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


// Main program:

int main(int argc, char *argv[])
{
    #include "include/addTimeOptions.H"
    #include "include/setRootCase.H"
    #include "include/createTime.H"
    #include "include/createMesh.H"

    wordList patchFieldTypes
    (
        mesh.boundaryMesh().size(),
        fvPatchFieldBase::calculatedType()
    );

    forAll(mesh.boundaryMesh(), patchi)
    {
        if (isA<mappedPolyPatch>(mesh.boundaryMesh()[patchi]))
        {
            patchFieldTypes[patchi] =
                mappedFixedValueFvPatchVectorField::typeName;
        }
    }

    Pout<< "patchFieldTypes:" << patchFieldTypes << endl;

    volVectorField cc
    (
        IOobject
        (
            "cc",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedVector(dimLength, Zero),
        patchFieldTypes
    );

    cc.primitiveFieldRef() = mesh.C().primitiveField();
    cc.boundaryFieldRef().updateCoeffs();

    forAll(cc.boundaryField(), patchi)
    {
        if
        (
            isA<mappedFixedValueFvPatchVectorField>
            (
                cc.boundaryField()[patchi]
            )
        )
        {
            Pout<< "Detected a mapped patch:" << patchi << endl;

            OFstream str(mesh.boundaryMesh()[patchi].name() + ".obj");
            Pout<< "Writing mapped values to " << str.name() << endl;

            label vertI = 0;
            const fvPatchVectorField& fvp = cc.boundaryField()[patchi];

            forAll(fvp, i)
            {
                meshTools::writeOBJ(str, fvp.patch().Cf()[i]);
                vertI++;
                meshTools::writeOBJ(str, fvp[i]);
                vertI++;
                str << "l " << vertI-1 << ' ' << vertI << nl;
            }
        }
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
