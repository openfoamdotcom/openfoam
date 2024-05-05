set(_FILES
  clouds/baseClasses/sprayCloud/sprayCloud.C
  parcels/derived/basicSprayParcel/defineBasicSprayParcel.C
  parcels/derived/basicSprayParcel/makeBasicSprayParcelSubmodels.C
)
add_library(lagrangianSpray ${_FILES})
target_compile_features(lagrangianSpray PUBLIC cxx_std_11)
target_compile_definitions(lagrangianSpray PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(lagrangianSpray PUBLIC dynamicFvMesh finiteArea lagrangianTurbulence regionFaModels surfaceFilmModels)
target_include_directories(lagrangianSpray PUBLIC
  .
)
install(TARGETS lagrangianSpray DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
