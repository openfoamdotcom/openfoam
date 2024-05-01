set(_FILES
  rhoSimpleFoam.C
)
add_executable(rhoSimpleFoam ${_FILES})
target_compile_features(rhoSimpleFoam PUBLIC cxx_std_11)
target_link_libraries(rhoSimpleFoam PUBLIC atmosphericModels finiteArea regionFaModels)
target_include_directories(rhoSimpleFoam PUBLIC
  .
)
