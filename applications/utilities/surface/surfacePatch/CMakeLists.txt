set(_FILES
  searchableSurfaceModifier/searchableSurfaceModifier.C
  searchableSurfaceModifier/autoPatch.C
  searchableSurfaceModifier/cut.C
  surfacePatch.C
)
add_executable(surfacePatch ${_FILES})
target_compile_features(surfacePatch PUBLIC cxx_std_11)
target_link_libraries(surfacePatch PUBLIC meshTools)
