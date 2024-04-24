set(_FILES
  faOption/faOption.C
  faOption/faOptionIO.C
  faOption/faOptionList.C
  faOption/faOptions.C
  faceSetOption/faceSetOption.C
  sources/derived/externalHeatFluxSource/externalHeatFluxSource.C
  sources/derived/jouleHeatingSource/jouleHeatingSource.C
  sources/derived/contactHeatFluxSource/contactHeatFluxSource.C
  sources/derived/externalFileSource/externalFileSource.C
  corrections/limitVelocity/limitVelocity.C
  corrections/limitHeight/limitHeight.C
)
add_library(faOptions ${_FILES})
target_compile_features(faOptions PUBLIC cxx_std_11)
target_compile_definitions(faOptions PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(faOptions PUBLIC
  faceSetOption
  sources/derived/externalHeatFluxSource
  sources/derived/externalFileSource
  sources/derived/contactHeatFluxSource
  sources/derived/jouleHeatingSource
  faOption
  corrections/limitHeight
  corrections/limitVelocity
)
install(TARGETS faOptions DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
