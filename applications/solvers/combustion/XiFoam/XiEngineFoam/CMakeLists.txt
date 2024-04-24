set(_FILES
  XiEngineFoam.C
)
add_executable(XiEngineFoam ${_FILES})
target_compile_features(XiEngineFoam PUBLIC cxx_std_11)
target_link_libraries(XiEngineFoam PUBLIC finiteVolume)
