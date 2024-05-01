set(_FILES
  mdFoam.C
)
add_executable(mdFoam ${_FILES})
target_compile_features(mdFoam PUBLIC cxx_std_11)
target_link_libraries(mdFoam PUBLIC molecularMeasurements molecule potential)
target_include_directories(mdFoam PUBLIC
  .
)
