set(_FILES
  foamFormatConvert.C
)
add_executable(foamFormatConvert ${_FILES})
target_compile_features(foamFormatConvert PUBLIC cxx_std_11)
target_link_libraries(foamFormatConvert PUBLIC genericPatchFields lagrangian)
target_include_directories(foamFormatConvert PUBLIC
  .
)
