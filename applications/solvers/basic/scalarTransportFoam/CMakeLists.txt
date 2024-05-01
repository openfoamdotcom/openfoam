set(_FILES
  scalarTransportFoam.C
)
add_executable(scalarTransportFoam ${_FILES})
target_compile_features(scalarTransportFoam PUBLIC cxx_std_11)
target_link_libraries(scalarTransportFoam PUBLIC fvOptions sampling)
target_include_directories(scalarTransportFoam PUBLIC
  .
)
