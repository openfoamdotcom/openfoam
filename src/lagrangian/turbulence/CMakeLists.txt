set(_FILES
  parcels/derived/basicKinematicParcel/makeBasicKinematicParcelSubmodels.C
  parcels/derived/basicKinematicCollidingParcel/makeBasicKinematicCollidingParcelSubmodels.C
  parcels/derived/basicThermoParcel/makeBasicThermoParcelSubmodels.C
  parcels/derived/basicReactingParcel/makeBasicReactingParcelSubmodels.C
  parcels/derived/basicReactingMultiphaseParcel/makeBasicReactingMultiphaseParcelSubmodels.C
  parcels/derived/basicKinematicMPPICParcel/makeBasicKinematicMPPICParcelSubmodels.C
  parcels/derived/basicHeterogeneousReactingParcel/makeBasicHeterogeneousParcelSubmodels.C
)
add_library(lagrangianTurbulence ${_FILES})
target_compile_features(lagrangianTurbulence PUBLIC cxx_std_11)
target_compile_definitions(lagrangianTurbulence PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(lagrangianTurbulence PUBLIC 
  parcels/include
  submodels/Thermodynamic/ParticleForces/BrownianMotion
  submodels/Kinematic/DispersionModel/StochasticDispersionRAS
  submodels/Kinematic/DispersionModel/DispersionRASModel
  submodels/Kinematic/DispersionModel/GradientDispersionRAS
)
install(TARGETS lagrangianTurbulence DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
