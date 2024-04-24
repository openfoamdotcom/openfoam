set(_FILES
  foamToCcm.C
)
add_executable(foamToCcm ${_FILES})
target_compile_features(foamToCcm PUBLIC cxx_std_11)
target_link_libraries(foamToCcm PUBLIC finiteVolume)
