set(_FILES
  mydebugSurfaceWriter.C
  Test-surface-sampling.C
)
add_executable(Test-surface-sampling ${_FILES})
target_compile_features(Test-surface-sampling PUBLIC cxx_std_11)
