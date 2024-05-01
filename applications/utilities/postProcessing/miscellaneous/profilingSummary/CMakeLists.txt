set(_FILES
  profilingSummary.C
)
add_executable(profilingSummary ${_FILES})
target_compile_features(profilingSummary PUBLIC cxx_std_11)
