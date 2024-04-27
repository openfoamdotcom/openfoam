set(_FILES
  ODESolvers/ODESolver/ODESolver.C
  ODESolvers/ODESolver/ODESolverNew.C
  ODESolvers/adaptiveSolver/adaptiveSolver.C
  ODESolvers/Euler/Euler.C
  ODESolvers/EulerSI/EulerSI.C
  ODESolvers/Trapezoid/Trapezoid.C
  ODESolvers/RKF45/RKF45.C
  ODESolvers/RKCK45/RKCK45.C
  ODESolvers/RKDP45/RKDP45.C
  ODESolvers/Rosenbrock12/Rosenbrock12.C
  ODESolvers/Rosenbrock23/Rosenbrock23.C
  ODESolvers/Rosenbrock34/Rosenbrock34.C
  ODESolvers/rodas23/rodas23.C
  ODESolvers/rodas34/rodas34.C
  ODESolvers/SIBS/SIBS.C
  ODESolvers/SIBS/SIMPR.C
  ODESolvers/SIBS/polyExtrapolate.C
  ODESolvers/seulex/seulex.C
)
add_library(ODE ${_FILES})
target_compile_features(ODE PUBLIC cxx_std_11)
target_compile_definitions(ODE PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(ODE PUBLIC OpenFOAM)
target_include_directories(ODE PUBLIC
  ODESystem
  ODESolvers/Rosenbrock34
  ODESolvers/rodas23
  ODESolvers/EulerSI
  ODESolvers/adaptiveSolver
  ODESolvers/RKCK45
  ODESolvers/SIBS
  ODESolvers/Euler
  ODESolvers/ODESolver
  ODESolvers/Trapezoid
  ODESolvers/seulex
  ODESolvers/Rosenbrock12
  ODESolvers/RKDP45
  ODESolvers/Rosenbrock23
  ODESolvers/rodas34
  ODESolvers/RKF45
)
install(TARGETS ODE DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
