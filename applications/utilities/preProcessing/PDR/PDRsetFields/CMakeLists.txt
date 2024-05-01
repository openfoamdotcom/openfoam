set(_FILES
  PDRsetFields.C
)
add_executable(PDRsetFields ${_FILES})
target_compile_features(PDRsetFields PUBLIC cxx_std_11)
target_link_libraries(PDRsetFields PUBLIC pdrFields)
