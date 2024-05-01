set(_FILES
  Test-triangleIntersection.C
)
add_executable(Test-triangleIntersection ${_FILES})
target_compile_features(Test-triangleIntersection PUBLIC cxx_std_11)
target_include_directories(Test-triangleIntersection PUBLIC
  .
)
