set(_FILES
  overRhoSimpleFoam.C
)
add_executable(overRhoSimpleFoam ${_FILES})
target_compile_features(overRhoSimpleFoam PUBLIC cxx_std_11)
target_link_libraries(overRhoSimpleFoam PUBLIC fvOptions overset thermoTools topoChangerFvMesh)
target_include_directories(overRhoSimpleFoam PUBLIC
  .
)
