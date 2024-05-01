set(_FILES
  kivaToFoam.C
)
add_executable(kivaToFoam ${_FILES})
target_compile_features(kivaToFoam PUBLIC cxx_std_11)
