set(_FILES
  boundaryInfo.C
  boundaryTemplates.C
  caseInfo.C
  solverTemplate.C
  createZeroDirectory.C
)
add_executable(createZeroDirectory ${_FILES})
target_compile_features(createZeroDirectory PUBLIC cxx_std_11)
target_link_libraries(createZeroDirectory PUBLIC finiteVolume)
