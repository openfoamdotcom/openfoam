#include "graphField/writePatchGraph.H"
#include "fields/volFields/volFields.H"
#include "fvMesh/fvMesh.H"
#include "graph/graph.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void Foam::writePatchGraph
(
    const volScalarField& vsf,
    const label patchLabel,
    const direction d,
    const word& graphFormat
)
{
    graph
    (
        vsf.name(),
        "position",
        vsf.name(),
        vsf.mesh().boundary()[patchLabel].Cf().component(d),
        vsf.boundaryField()[patchLabel]
    ).write(vsf.time().timePath()/vsf.name(), graphFormat);
}


// ************************************************************************* //
