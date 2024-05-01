set(_FILES
  gmshToFoam.C
)
add_executable(gmshToFoam ${_FILES})
target_compile_features(gmshToFoam PUBLIC cxx_std_11)
target_link_libraries(gmshToFoam PUBLIC dynamicMesh meshTools)
target_include_directories(gmshToFoam PUBLIC
  .
)
