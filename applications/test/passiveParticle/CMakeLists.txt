set(_FILES
)
add_executable(Test-passiveParticle ${_FILES})
target_compile_features(Test-passiveParticle PUBLIC cxx_std_11)
target_include_directories(Test-passiveParticle PUBLIC
  .
)
