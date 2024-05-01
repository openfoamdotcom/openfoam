set(_FILES
  XiFoam.C
)
add_executable(XiFoam ${_FILES})
target_compile_features(XiFoam PUBLIC cxx_std_11)
target_link_libraries(XiFoam PUBLIC engine thermoTools laminarFlameSpeedModels)
