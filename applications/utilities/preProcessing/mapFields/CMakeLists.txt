set(_FILES
  mapLagrangian.C
  mapFields.C
)
add_executable(mapFields ${_FILES})
target_compile_features(mapFields PUBLIC cxx_std_11)
target_link_libraries(mapFields PUBLIC decompose decompositionMethods genericPatchFields sampling)
target_include_directories(mapFields PUBLIC
  .
)
