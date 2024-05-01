set(_FILES
  Test-PointEdgeWave.C
)
add_executable(Test-PointEdgeWave ${_FILES})
target_compile_features(Test-PointEdgeWave PUBLIC cxx_std_11)
