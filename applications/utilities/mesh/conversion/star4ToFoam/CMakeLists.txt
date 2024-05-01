set(_FILES
  star4ToFoam.C
)
add_executable(star4ToFoam ${_FILES})
target_compile_features(star4ToFoam PUBLIC cxx_std_11)
target_link_libraries(star4ToFoam PUBLIC conversion)
