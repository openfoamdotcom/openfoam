set(_FILES
  simpleFoam.C
)
add_executable(simpleFoam ${_FILES})
target_compile_features(simpleFoam PUBLIC cxx_std_11)
target_link_libraries(simpleFoam PUBLIC atmosphericModels)
