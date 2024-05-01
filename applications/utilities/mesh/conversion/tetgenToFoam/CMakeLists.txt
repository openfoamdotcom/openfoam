set(_FILES
  tetgenToFoam.C
)
add_executable(tetgenToFoam ${_FILES})
target_compile_features(tetgenToFoam PUBLIC cxx_std_11)
target_include_directories(tetgenToFoam PUBLIC
  .
)
