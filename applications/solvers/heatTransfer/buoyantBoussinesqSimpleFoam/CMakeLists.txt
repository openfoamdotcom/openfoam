set(_FILES
  buoyantBoussinesqSimpleFoam.C
)
add_executable(buoyantBoussinesqSimpleFoam ${_FILES})
target_compile_features(buoyantBoussinesqSimpleFoam PUBLIC cxx_std_11)
target_link_libraries(buoyantBoussinesqSimpleFoam PUBLIC atmosphericModels)
target_include_directories(buoyantBoussinesqSimpleFoam PUBLIC
  .
)
