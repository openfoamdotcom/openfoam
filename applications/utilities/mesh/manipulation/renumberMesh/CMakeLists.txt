set(_FILES
  renumberMesh.C
)
add_executable(renumberMesh ${_FILES})
target_compile_features(renumberMesh PUBLIC cxx_std_11)
target_link_libraries(renumberMesh PUBLIC genericPatchFields metisDecomp reconstruct renumberMethods)
if (KAHIP_FOUND)
  target_link_libraries(renumberMesh PUBLIC kahipDecomp)
endif()
if (SCOTCH_FOUND)
  target_link_libraries(renumberMesh PUBLIC scotchDecomp)
endif()
target_include_directories(renumberMesh PUBLIC
  .
)
