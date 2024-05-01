set(_FILES
  dsmcInitialise.C
)
add_executable(dsmcInitialise ${_FILES})
target_compile_features(dsmcInitialise PUBLIC cxx_std_11)
target_link_libraries(dsmcInitialise PUBLIC DSMC)
