set(_FILES
  simpleFoam.C
)
add_executable(simpleFoam ${_FILES})
target_compile_features(simpleFoam PUBLIC cxx_std_11)
target_link_libraries(simpleFoam PUBLIC atmosphericModels)
target_include_directories(simpleFoam PUBLIC
  .
  ${PROJECT_SOURCE_DIR}/src/OpenFOAM/include
  ${PROJECT_SOURCE_DIR}/src/finiteVolume/cfdTools/general/solutionControl
)
