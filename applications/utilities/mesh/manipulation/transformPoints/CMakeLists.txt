set(_FILES
  transformPoints.C
)
add_executable(transformPoints ${_FILES})
target_compile_features(transformPoints PUBLIC cxx_std_11)
target_link_libraries(transformPoints PUBLIC genericPatchFields)
