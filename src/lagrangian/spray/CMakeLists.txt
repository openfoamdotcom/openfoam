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
  parcels/derived/basicSprayParcel
  parcels/include
  parcels/Templates/SprayParcel
  submodels/AtomizationModel/LISAAtomization
  submodels/AtomizationModel/NoAtomization
  submodels/AtomizationModel/AtomizationModel
  submodels/AtomizationModel/BlobsSheetAtomization
  submodels/BreakupModel/ReitzDiwakar
  submodels/BreakupModel/PilchErdman
  submodels/BreakupModel/ETAB
  submodels/BreakupModel/ReitzKHRT
  submodels/BreakupModel/TAB
  submodels/BreakupModel/SHF
  submodels/BreakupModel/BreakupModel
  submodels/BreakupModel/NoBreakup
  submodels/StochasticCollision/TrajectoryCollision
  submodels/StochasticCollision/ORourkeCollision
  clouds/baseClasses/sprayCloud
  clouds/derived/basicSprayCloud
  clouds/Templates/SprayCloud
)
install(TARGETS lagrangianSpray DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
