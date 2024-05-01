set(_FILES
  ideasUnvToFoam.C
)
add_executable(ideasUnvToFoam ${_FILES})
target_compile_features(ideasUnvToFoam PUBLIC cxx_std_11)
target_link_libraries(ideasUnvToFoam PUBLIC meshTools surfMesh)
target_include_directories(ideasUnvToFoam PUBLIC
  .
)
