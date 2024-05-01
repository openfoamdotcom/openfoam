set(_FILES
  Test-decomposedBlockData.C
)
add_executable(Test-decomposedBlockData ${_FILES})
target_compile_features(Test-decomposedBlockData PUBLIC cxx_std_11)
target_include_directories(Test-decomposedBlockData PUBLIC
  .
)
