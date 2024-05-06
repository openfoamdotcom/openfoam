// Some test code

#include "include/foamVersion.H"
#include "db/IOstreams/IOstreams.H"

namespace Foam
{
    void printTest()
    {
        Info<< nl;
        foamVersion::printBuildInfo(Info.stdStream());
    }
}
