set(_FILES
  Test-PrimitivePatch.C
)
add_executable(Test-PrimitivePatch ${_FILES})
target_compile_features(Test-PrimitivePatch PUBLIC cxx_std_11)
