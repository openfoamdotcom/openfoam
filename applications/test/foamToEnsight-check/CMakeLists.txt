set(_FILES
  foamToEnsight-check.C
)
add_executable(foamToEnsight-check ${_FILES})
target_compile_features(foamToEnsight-check PUBLIC cxx_std_11)
target_link_libraries(foamToEnsight-check PUBLIC conversion genericPatchFields lagrangianIntermediate)
target_include_directories(foamToEnsight-check PUBLIC
  .
)
