set(_FILES
  forces/forces.C
  forceCoeffs/forceCoeffs.C
  propellerInfo/propellerInfo.C
)
add_library(forces ${_FILES})
target_compile_features(forces PUBLIC cxx_std_11)
target_compile_definitions(forces PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(forces PUBLIC incompressibleTurbulenceModels compressibleTurbulenceModels specie)
target_include_directories(forces PUBLIC
  forceCoeffs
  propellerInfo
  forces
)
install(TARGETS forces DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
