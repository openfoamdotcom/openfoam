set(_FILES
  foamHasLibrary.C
)
add_executable(foamHasLibrary ${_FILES})
target_compile_features(foamHasLibrary PUBLIC cxx_std_11)
