set(_FILES
  foamRestoreFields.C
)
add_executable(foamRestoreFields ${_FILES})
target_compile_features(foamRestoreFields PUBLIC cxx_std_11)
target_link_libraries(foamRestoreFields PUBLIC meshTools)
target_include_directories(foamRestoreFields PUBLIC
  .
)
