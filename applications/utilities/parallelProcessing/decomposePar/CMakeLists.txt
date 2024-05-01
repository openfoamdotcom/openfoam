set(_FILES
  decomposePar.C
  domainDecomposition.C
  domainDecompositionMesh.C
  domainDecompositionDistribute.C
  domainDecompositionWrite.C
  domainDecompositionDryRun.C
  domainDecompositionDryRunWrite.C
)
add_executable(decomposePar ${_FILES})
target_compile_features(decomposePar PUBLIC cxx_std_11)
target_link_libraries(decomposePar PUBLIC decompose faDecompose genericPatchFields metisDecomp)
if (KAHIP_FOUND)
  target_link_libraries(decomposePar PUBLIC kahipDecomp)
endif()
if (SCOTCH_FOUND)
  target_link_libraries(decomposePar PUBLIC scotchDecomp)
endif()
target_include_directories(decomposePar PUBLIC
  .
)
