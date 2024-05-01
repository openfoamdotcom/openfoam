set(_FILES
  smapToFoam.C
)
add_executable(smapToFoam ${_FILES})
target_compile_features(smapToFoam PUBLIC cxx_std_11)
target_link_libraries(smapToFoam PUBLIC genericPatchFields)
