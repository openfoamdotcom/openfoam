#include "fvMesh/fvMesh.H"

namespace Foam
{
    void writeFields
    (
        const fvMesh& mesh,
        const wordHashSet& selectedFields,
        const bool writeFaceFields
    );
}
