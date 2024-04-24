set(_FILES
  coldEngineFoam.C
)
add_executable(coldEngineFoam ${_FILES})
target_compile_features(coldEngineFoam PUBLIC cxx_std_11)
target_link_libraries(coldEngineFoam PUBLIC finiteVolume)
