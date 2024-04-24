set(_FILES
  vtkUnstructuredToFoam.C
)
add_executable(vtkUnstructuredToFoam ${_FILES})
target_compile_features(vtkUnstructuredToFoam PUBLIC cxx_std_11)
target_link_libraries(vtkUnstructuredToFoam PUBLIC finiteVolume)
