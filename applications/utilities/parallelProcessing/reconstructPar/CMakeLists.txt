set(_FILES
  reconstructPar.C
)
add_executable(reconstructPar ${_FILES})
target_compile_features(reconstructPar PUBLIC cxx_std_11)
target_link_libraries(reconstructPar PUBLIC dynamicMesh faReconstruct genericPatchFields reconstruct)
target_include_directories(reconstructPar PUBLIC
  .
)
