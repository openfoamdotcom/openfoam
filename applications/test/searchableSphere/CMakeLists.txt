set(_FILES
  Test-searchableSphere.C
)
add_executable(Test-searchableSphere ${_FILES})
target_compile_features(Test-searchableSphere PUBLIC cxx_std_11)
