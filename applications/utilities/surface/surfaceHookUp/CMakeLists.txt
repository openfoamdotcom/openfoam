set(_FILES
  surfaceHookUp.C
)
add_executable(surfaceHookUp ${_FILES})
target_compile_features(surfaceHookUp PUBLIC cxx_std_11)
target_link_libraries(surfaceHookUp PUBLIC meshTools)
target_include_directories(surfaceHookUp PUBLIC
  .
)
