set(_FILES
  overRhoPimpleDyMFoam.C
)
add_executable(overRhoPimpleDyMFoam ${_FILES})
target_compile_features(overRhoPimpleDyMFoam PUBLIC cxx_std_11)
target_link_libraries(overRhoPimpleDyMFoam PUBLIC fvOptions overset thermoTools topoChangerFvMesh)
target_include_directories(overRhoPimpleDyMFoam PUBLIC
  .
)
