set(_FILES
  extrude2DMeshApp.C
)
add_executable(extrude2DMesh ${_FILES})
target_compile_features(extrude2DMesh PUBLIC cxx_std_11)
target_link_libraries(extrude2DMesh PUBLIC finiteVolume)
