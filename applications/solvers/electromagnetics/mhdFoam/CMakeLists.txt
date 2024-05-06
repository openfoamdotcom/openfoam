set(_FILES
  mhdFoam.C
)
add_executable(mhdFoam ${_FILES})
target_compile_features(mhdFoam PUBLIC cxx_std_11)
target_link_libraries(mhdFoam PUBLIC finiteVolume meshTools)
target_include_directories(mhdFoam PUBLIC
  .
  ${PROJECT_SOURCE_DIR}/src/OpenFOAM/include
  ${PROJECT_SOURCE_DIR}/src/finiteVolume/cfdTools/general/solutionControl
)
