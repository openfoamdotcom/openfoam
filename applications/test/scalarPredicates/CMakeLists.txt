set(_FILES
  Test-scalarPredicates.C
)
add_executable(Test-scalarPredicates ${_FILES})
target_compile_features(Test-scalarPredicates PUBLIC cxx_std_11)
target_include_directories(Test-scalarPredicates PUBLIC
  .
)
