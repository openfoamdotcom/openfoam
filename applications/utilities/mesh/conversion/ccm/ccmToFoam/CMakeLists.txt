set(_FILES
  ccmToFoam.C
)
add_executable(ccmToFoam ${_FILES})
target_compile_features(ccmToFoam PUBLIC cxx_std_11)
target_link_libraries(ccmToFoam PUBLIC ccm genericPatchFields)
