set(_FILES
  alphatFilmWallFunction/alphatFilmWallFunctionFvPatchScalarField.C
  nutkFilmWallFunction/nutkFilmWallFunctionFvPatchScalarField.C
)
add_library(surfaceFilmDerivedFvPatchFields ${_FILES})
target_compile_features(surfaceFilmDerivedFvPatchFields PUBLIC cxx_std_11)
target_compile_definitions(surfaceFilmDerivedFvPatchFields PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(surfaceFilmDerivedFvPatchFields PUBLIC
  alphatFilmWallFunction
  nutkFilmWallFunction
)
install(TARGETS surfaceFilmDerivedFvPatchFields DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
