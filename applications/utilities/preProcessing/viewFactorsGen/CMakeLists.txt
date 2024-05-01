set(_FILES
  viewFactorsGen.C
)
add_executable(viewFactorsGen ${_FILES})
target_compile_features(viewFactorsGen PUBLIC cxx_std_11)
target_link_libraries(viewFactorsGen PUBLIC radiationModels)
target_include_directories(viewFactorsGen PUBLIC
  .
)
