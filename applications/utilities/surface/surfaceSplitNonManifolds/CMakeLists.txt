set(_FILES
  surfaceSplitNonManifolds.C
)
add_executable(surfaceSplitNonManifolds ${_FILES})
target_compile_features(surfaceSplitNonManifolds PUBLIC cxx_std_11)
target_link_libraries(surfaceSplitNonManifolds PUBLIC meshTools)
