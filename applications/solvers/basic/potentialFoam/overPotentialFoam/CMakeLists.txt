set(_FILES
  overPotentialFoam.C
)
add_executable(overPotentialFoam ${_FILES})
target_compile_features(overPotentialFoam PUBLIC cxx_std_11)
target_link_libraries(overPotentialFoam PUBLIC overset)
target_include_directories(overPotentialFoam PUBLIC
  .
)
