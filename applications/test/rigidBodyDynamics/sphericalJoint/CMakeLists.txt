set(_FILES
  sphericalJoint.C
)
add_executable(Test-sphericalJoint ${_FILES})
target_compile_features(Test-sphericalJoint PUBLIC cxx_std_11)
