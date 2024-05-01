set(_FILES
  buoyantSimpleFoam.C
)
add_executable(buoyantSimpleFoam ${_FILES})
target_compile_features(buoyantSimpleFoam PUBLIC cxx_std_11)
target_link_libraries(buoyantSimpleFoam PUBLIC atmosphericModels regionFaModels finiteArea)
