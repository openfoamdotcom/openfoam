set(_FILES
  mshToFoam.C
)
add_executable(mshToFoam ${_FILES})
target_compile_features(mshToFoam PUBLIC cxx_std_11)
target_include_directories(mshToFoam PUBLIC
  .
)
