set(_FILES
  pyrolysisModel/pyrolysisModel.C
  pyrolysisModel/pyrolysisModelNew.C
  reactingOneDim/reactingOneDim.C
  noPyrolysis/noPyrolysis.C
  thermo/thermo.C
  pyrolysisModel/pyrolysisModelCollection.C
)
add_library(pyrolysisModels ${_FILES})
target_compile_features(pyrolysisModels PUBLIC cxx_std_11)
set_property(TARGET pyrolysisModels PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(pyrolysisModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(pyrolysisModels PUBLIC compressibleTurbulenceModels radiationModels reactionThermophysicalModels regionModels solidChemistryModel)
target_include_directories(pyrolysisModels PUBLIC
  .
)
install(TARGETS pyrolysisModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
