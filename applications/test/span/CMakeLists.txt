set(_FILES
  Test-stdFoam-span.C
)
add_executable(Test-stdFoam-span ${_FILES})
target_compile_features(Test-stdFoam-span PUBLIC cxx_std_11)
