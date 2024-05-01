set(_FILES
  chtMultiRegionSimpleFoam.C
)
add_executable(chtMultiRegionSimpleFoam ${_FILES})
target_compile_features(chtMultiRegionSimpleFoam PUBLIC cxx_std_11)
target_link_libraries(chtMultiRegionSimpleFoam PUBLIC finiteArea fvOptions regionFaModels regionModels)
target_include_directories(chtMultiRegionSimpleFoam PUBLIC
  .
)
