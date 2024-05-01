set(_FILES
  WatersKing.C
)
add_executable(WatersKing ${_FILES})
target_compile_features(WatersKing PUBLIC cxx_std_11)
target_link_libraries(WatersKing PUBLIC incompressibleTransportModels incompressibleTurbulenceModels)
