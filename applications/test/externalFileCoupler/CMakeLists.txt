set(_FILES
  Test-externalFileCoupler.C
)
add_executable(Test-externalFileCoupler ${_FILES})
target_compile_features(Test-externalFileCoupler PUBLIC cxx_std_11)
target_include_directories(Test-externalFileCoupler PUBLIC
  .
)
