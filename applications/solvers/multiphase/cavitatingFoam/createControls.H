#include "cfdTools/general/include/createTimeControls.H"

scalar maxAcousticCo
(
    runTime.controlDict().get<scalar>("maxAcousticCo")
);
