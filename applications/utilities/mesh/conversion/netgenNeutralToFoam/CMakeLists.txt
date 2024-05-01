set(_FILES
  netgenNeutralToFoam.C
)
add_executable(netgenNeutralToFoam ${_FILES})
target_compile_features(netgenNeutralToFoam PUBLIC cxx_std_11)
target_include_directories(netgenNeutralToFoam PUBLIC
  .
)
