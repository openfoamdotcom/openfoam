set(_FILES
  fireToFoam.C
)
add_executable(fireToFoam ${_FILES})
target_compile_features(fireToFoam PUBLIC cxx_std_11)
target_link_libraries(fireToFoam PUBLIC conversion)
target_include_directories(fireToFoam PUBLIC
  .
)
