set(_FILES
  foamToMetisGraph.C
)
add_executable(foamToMetisGraph ${_FILES})
target_compile_features(foamToMetisGraph PUBLIC cxx_std_11)
target_include_directories(foamToMetisGraph PUBLIC
  .
)
