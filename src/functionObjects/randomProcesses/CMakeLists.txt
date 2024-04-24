set(_FILES
  energySpectrum/energySpectrum.C
)
add_library(randomProcessesFunctionObjects ${_FILES})
target_compile_features(randomProcessesFunctionObjects PUBLIC cxx_std_11)
target_compile_definitions(randomProcessesFunctionObjects PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(randomProcessesFunctionObjects PUBLIC
  energySpectrum
)
install(TARGETS randomProcessesFunctionObjects DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
