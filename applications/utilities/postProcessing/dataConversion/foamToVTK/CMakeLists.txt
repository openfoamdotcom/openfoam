set(_FILES
  foamToVTK.C
)
add_executable(foamToVTK ${_FILES})
target_compile_features(foamToVTK PUBLIC cxx_std_11)
target_link_libraries(foamToVTK PUBLIC conversion genericPatchFields lagrangianIntermediate)
target_include_directories(foamToVTK PUBLIC
  .
)
