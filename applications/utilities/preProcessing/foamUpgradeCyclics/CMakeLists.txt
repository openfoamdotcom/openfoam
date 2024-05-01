set(_FILES
  foamUpgradeCyclics.C
)
add_executable(foamUpgradeCyclics ${_FILES})
target_compile_features(foamUpgradeCyclics PUBLIC cxx_std_11)
target_link_libraries(foamUpgradeCyclics PUBLIC genericPatchFields)
target_include_directories(foamUpgradeCyclics PUBLIC
  .
)
