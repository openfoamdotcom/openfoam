set(_FILES
  mdEquilibrationFoam.C
)
add_executable(mdEquilibrationFoam ${_FILES})
target_compile_features(mdEquilibrationFoam PUBLIC cxx_std_11)
target_link_libraries(mdEquilibrationFoam PUBLIC molecularMeasurements molecule potential)
target_include_directories(mdEquilibrationFoam PUBLIC
  .
)
