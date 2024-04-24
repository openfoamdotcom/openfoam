set(_FILES
  twoPhaseSystem.C
  twoPhaseSystemNew.C
  twoPhaseSystems.C
  diameterModels/IATE/IATE.C
  diameterModels/IATE/IATEsources/IATEsource/IATEsource.C
  diameterModels/IATE/IATEsources/wakeEntrainmentCoalescence/wakeEntrainmentCoalescence.C
  diameterModels/IATE/IATEsources/turbulentBreakUp/turbulentBreakUp.C
  diameterModels/IATE/IATEsources/randomCoalescence/randomCoalescence.C
  diameterModels/IATE/IATEsources/phaseChange/phaseChange.C
  diameterModels/IATE/IATEsources/wallBoiling/wallBoiling.C
)
add_library(reactingTwoPhaseSystem ${_FILES})
target_compile_features(reactingTwoPhaseSystem PUBLIC cxx_std_11)
target_compile_definitions(reactingTwoPhaseSystem PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(reactingTwoPhaseSystem PUBLIC
  .
  diameterModels/IATE
  diameterModels/IATE/IATEsources/dummy
  diameterModels/IATE/IATEsources/IATEsource
  diameterModels/IATE/IATEsources/wallBoiling
  diameterModels/IATE/IATEsources/turbulentBreakUp
  diameterModels/IATE/IATEsources/phaseChange
  diameterModels/IATE/IATEsources/randomCoalescence
  diameterModels/IATE/IATEsources/wakeEntrainmentCoalescence
)
install(TARGETS reactingTwoPhaseSystem DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
