set(_FILES
  coalParcel/makeCoalParcelSubmodels.C
  coalCloudList/coalCloudList.C
)
add_library(coalCombustion ${_FILES})
target_compile_features(coalCombustion PUBLIC cxx_std_11)
set_property(TARGET coalCombustion PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(coalCombustion PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(coalCombustion PUBLIC dynamicFvMesh finiteArea lagrangianTurbulence regionFaModels surfaceFilmModels)
target_include_directories(coalCombustion PUBLIC
  .
)
install(TARGETS coalCombustion DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
