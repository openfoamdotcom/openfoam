set(_FILES
  renumberMesh.C
)
add_executable(renumberMesh ${_FILES})
target_compile_features(renumberMesh PUBLIC cxx_std_11)
target_link_libraries(renumberMesh PUBLIC genericPatchFields renumberMethods reconstruct kahipDecomp metisDecomp scotchDecomp)
