set(_FILES
  surfaceLambdaMuSmooth.C
)
add_executable(surfaceLambdaMuSmooth ${_FILES})
target_compile_features(surfaceLambdaMuSmooth PUBLIC cxx_std_11)
target_link_libraries(surfaceLambdaMuSmooth PUBLIC meshTools)
target_include_directories(surfaceLambdaMuSmooth PUBLIC
  .
)
