set(_FILES
  mapLagrangian.C
  mapFieldsPar.C
)
add_executable(mapFieldsPar ${_FILES})
target_compile_features(mapFieldsPar PUBLIC cxx_std_11)
target_link_libraries(mapFieldsPar PUBLIC genericPatchFields lagrangian sampling)
