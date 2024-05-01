set(_FILES
  writeMeshObj.C
)
add_executable(writeMeshObj ${_FILES})
target_compile_features(writeMeshObj PUBLIC cxx_std_11)
target_link_libraries(writeMeshObj PUBLIC meshTools)
