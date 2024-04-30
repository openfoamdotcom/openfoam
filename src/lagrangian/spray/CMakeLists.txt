set(_FILES
  clouds/baseClasses/sprayCloud/sprayCloud.C
  parcels/derived/basicSprayParcel/defineBasicSprayParcel.C
  parcels/derived/basicSprayParcel/makeBasicSprayParcelSubmodels.C
)
add_library(lagrangianSpray ${_FILES})
target_compile_features(lagrangianSpray PUBLIC cxx_std_11)
target_compile_definitions(lagrangianSpray PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(lagrangianSpray PUBLIC lagrangianTurbulence surfaceFilmModels dynamicFvMesh regionFaModels finiteArea)
target_include_directories(lagrangianSpray PUBLIC
  clouds/Templates/SprayCloud
  clouds/baseClasses/sprayCloud
  clouds/derived/basicSprayCloud
  parcels/Templates/SprayParcel
  parcels/derived/basicSprayParcel
  parcels/include
  submodels/AtomizationModel/AtomizationModel
  submodels/AtomizationModel/BlobsSheetAtomization
  submodels/AtomizationModel/LISAAtomization
  submodels/AtomizationModel/NoAtomization
  submodels/BreakupModel/BreakupModel
  submodels/BreakupModel/ETAB
  submodels/BreakupModel/NoBreakup
  submodels/BreakupModel/PilchErdman
  submodels/BreakupModel/ReitzDiwakar
  submodels/BreakupModel/ReitzKHRT
  submodels/BreakupModel/SHF
  submodels/BreakupModel/TAB
  submodels/StochasticCollision/ORourkeCollision
  submodels/StochasticCollision/TrajectoryCollision
)
install(TARGETS lagrangianSpray DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
