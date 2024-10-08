if (nAlphaSubCycles > 1)
{
    dimensionedScalar totalDeltaT = runTime.deltaT();
    surfaceScalarField rhoPhiSum
    (
        IOobject
        (
            "rhoPhiSum",
            runTime.timeName(),
            mesh
        ),
        mesh,
        dimensionedScalar(rhoPhi.dimensions(), Zero)
    );

    for
    (
        subCycle<volScalarField> alphaSubCycle(alpha1, nAlphaSubCycles);
        !(++alphaSubCycle).end();
    )
    {
        #include "solvers/multiphase/VoF/alphaEqn.H"
        rhoPhiSum += (runTime.deltaT()/totalDeltaT)*rhoPhi;
    }

    rhoPhi = rhoPhiSum;
}
else
{
    #include "solvers/multiphase/VoF/alphaEqn.H"
}

{
    volScalarField rhoNew(alpha1*rho1 + alpha2*rho2 + alpha3*rho3);

    //solve(fvm::ddt(rho) + fvc::div(rhoPhi));
    //Info<< "density error = "
    //    << max((mag(rho - rhoNew)/mag(rhoNew))().primitiveField()) << endl;

    rho == rhoNew;
}
