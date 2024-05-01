set(_FILES
  laplacianFoam.C
)
add_executable(laplacianFoam ${_FILES})
target_compile_features(laplacianFoam PUBLIC cxx_std_11)
target_link_libraries(laplacianFoam PUBLIC fvOptions meshTools)
