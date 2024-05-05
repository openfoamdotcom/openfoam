#ifndef faCFD_H
#define faCFD_H

#include "db/Time/TimeOpenFOAM.H"
#include "faMesh/faMesh.H"
#include "fields/areaFields/areaFields.H"
#include "fields/edgeFields/edgeFields.H"
#include "faMatrices/faMatrices.H"
#include "finiteArea/fam/fam.H"
#include "finiteArea/fac/fac.H"
#include "interpolation/volSurfaceMapping/volSurfaceMapping.H"

#include "include/OSspecific.H"
#include "global/argList/argList.H"
#include "db/Time/timeSelector.H"

#ifndef namespaceFoam
#define namespaceFoam
    using namespace Foam;
#endif

#endif
