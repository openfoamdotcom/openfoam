set(_FILES
  buoyantPimpleFoam.C
)
add_executable(buoyantPimpleFoam ${_FILES})
target_compile_features(buoyantPimpleFoam PUBLIC cxx_std_11)
target_link_libraries(buoyantPimpleFoam PUBLIC finiteVolume)
