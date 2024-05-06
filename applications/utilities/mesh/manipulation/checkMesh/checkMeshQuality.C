#include "checkMeshQuality.H"
#include "meshes/polyMesh/polyMesh.H"
#include "topoSet/topoSets/cellSet.H"
#include "topoSet/topoSets/faceSet.H"
#include "motionSmoother/motionSmoother.H"
#include "writers/common/surfaceWriter.H"
#include "checkTools.H"

Foam::label Foam::checkMeshQuality
(
    const polyMesh& mesh,
    const dictionary& dict,
    autoPtr<surfaceWriter>& writer
)
{
    label noFailedChecks = 0;

    {
        faceSet faces(mesh, "meshQualityFaces", mesh.nFaces()/100+1);
        motionSmoother::checkMesh(false, mesh, dict, faces);

        label nFaces = returnReduce(faces.size(), sumOp<label>());

        if (nFaces > 0)
        {
            noFailedChecks++;

            Info<< "  <<Writing " << nFaces
                << " faces in error to set " << faces.name() << endl;
            faces.instance() = mesh.pointsInstance();
            faces.write();

            if (writer)
            {
                mergeAndWrite(*writer, faces);
            }
        }
    }

    return noFailedChecks;
}
