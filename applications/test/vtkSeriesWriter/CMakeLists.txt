set(_FILES
  Test-vtkSeriesWriter.C
)
add_executable(Test-vtkSeriesWriter ${_FILES})
target_compile_features(Test-vtkSeriesWriter PUBLIC cxx_std_11)
target_include_directories(Test-vtkSeriesWriter PUBLIC
  .
)
