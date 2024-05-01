set(_FILES
  Test-foamVersion.C
)
add_executable(Test-foamVersion ${_FILES})
target_compile_features(Test-foamVersion PUBLIC cxx_std_11)
target_include_directories(Test-foamVersion PUBLIC
  .
)
