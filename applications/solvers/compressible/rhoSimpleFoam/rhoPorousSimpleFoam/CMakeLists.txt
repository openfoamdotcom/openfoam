set(_FILES
  rhoPorousSimpleFoam.C
)
add_executable(rhoPorousSimpleFoam ${_FILES})
target_compile_features(rhoPorousSimpleFoam PUBLIC cxx_std_11)
target_link_libraries(rhoPorousSimpleFoam PUBLIC finiteVolume)
