set(_FILES
  chemFoam.C
)
add_executable(chemFoam ${_FILES})
target_compile_features(chemFoam PUBLIC cxx_std_11)
target_link_libraries(chemFoam PUBLIC chemistryModel thermophysicalProperties)
