set(_FILES
  PDRblockMesh.C
)
add_executable(PDRblockMesh ${_FILES})
target_compile_features(PDRblockMesh PUBLIC cxx_std_11)
target_link_libraries(PDRblockMesh PUBLIC blockMeshLib)
target_include_directories(PDRblockMesh PUBLIC
  .
)
