set(_FILES
)
add_library(TestDummy-OpenFOAM ${_FILES})
target_compile_features(TestDummy-OpenFOAM PUBLIC cxx_std_11)
target_compile_definitions(TestDummy-OpenFOAM PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(TestDummy-OpenFOAM PUBLIC
  .
)
install(TARGETS TestDummy-OpenFOAM DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
