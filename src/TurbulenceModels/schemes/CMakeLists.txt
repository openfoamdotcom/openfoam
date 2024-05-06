set(_FILES
  DEShybrid/DEShybrid.C
)
add_library(turbulenceModelSchemes ${_FILES})
target_compile_features(turbulenceModelSchemes PUBLIC cxx_std_11)
set_property(TARGET turbulenceModelSchemes PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(turbulenceModelSchemes PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(turbulenceModelSchemes PUBLIC turbulenceModels)
target_include_directories(turbulenceModelSchemes PUBLIC
  .
)
install(TARGETS turbulenceModelSchemes DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
