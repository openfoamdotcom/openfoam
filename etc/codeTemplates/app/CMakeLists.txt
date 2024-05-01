set(_FILES
  NAME.C
)
add_executable(NAME ${_FILES})
target_compile_features(NAME PUBLIC cxx_std_11)
target_link_libraries(NAME PUBLIC finiteVolume meshTools)
