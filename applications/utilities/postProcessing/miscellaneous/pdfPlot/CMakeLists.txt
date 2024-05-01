set(_FILES
  pdfPlot.C
)
add_executable(pdfPlot ${_FILES})
target_compile_features(pdfPlot PUBLIC cxx_std_11)
target_link_libraries(pdfPlot PUBLIC sampling distributionModels)
