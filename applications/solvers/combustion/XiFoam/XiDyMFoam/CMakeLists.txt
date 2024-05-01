set(_FILES
  XiDyMFoam.C
)
add_executable(XiDyMFoam ${_FILES})
target_compile_features(XiDyMFoam PUBLIC cxx_std_11)
target_link_libraries(XiDyMFoam PUBLIC engine laminarFlameSpeedModels thermoTools topoChangerFvMesh)
target_include_directories(XiDyMFoam PUBLIC
  .
)
