set(_FILES
  reducedUnits/reducedUnits.C
  reducedUnits/reducedUnitsIO.C
  molecule/molecule.C
  molecule/moleculeIO.C
  moleculeCloud/moleculeCloud.C
)
add_library(molecule ${_FILES})
target_compile_features(molecule PUBLIC cxx_std_11)
target_compile_definitions(molecule PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(molecule PUBLIC 
  reducedUnits
  molecule
  moleculeCloud
)
install(TARGETS molecule DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
