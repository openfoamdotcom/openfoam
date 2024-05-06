if (finalIter)
{
    mesh.data().setFinalIteration(true);
}

if (frozenFlow)
{
    #include "fluid/EEqn.H"
}
else
{
    if (oCorr == 0)
    {
        #include "cfdTools/compressible/rhoEqn.H"
    }

    #include "fluid/UEqn.H"
    #include "fluid/YEqn.H"
    #include "fluid/EEqn.H"

    if (!coupled)
    {
        Info<< "\nSolving for fluid region " << fluidRegions[i].name() << endl;

        // --- PISO loop
        for (int corr=0; corr<nCorr; corr++)
        {
            #include "fluid/pEqn.H"
        }

        turbulence.correct();

        rho = thermo.rho();
    }
}

if (finalIter)
{
    mesh.data().setFinalIteration(false);
}
