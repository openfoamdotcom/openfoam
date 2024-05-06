set(_FILES
  tabulatedWallFunction/tabulatedWallFunction.C
  tabulatedWallFunction/tabulatedWallFunctionNew.C
  SpaldingsLaw/SpaldingsLaw.C
  general/general.C
)
add_library(tabulatedWallFunctions ${_FILES})
target_compile_features(tabulatedWallFunctions PUBLIC cxx_std_11)
set_property(TARGET tabulatedWallFunctions PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(tabulatedWallFunctions PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(tabulatedWallFunctions PUBLIC finiteVolume)
target_include_directories(tabulatedWallFunctions PUBLIC
  .
)
install(TARGETS tabulatedWallFunctions DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
