set(_FILES
  surfaceCheck.C
)
add_executable(surfaceCheck ${_FILES})
target_compile_features(surfaceCheck PUBLIC cxx_std_11)
target_link_libraries(surfaceCheck PUBLIC meshTools)
