set(_FILES
  buoyantBoussinesqPimpleFoam.C
)
add_executable(buoyantBoussinesqPimpleFoam ${_FILES})
target_compile_features(buoyantBoussinesqPimpleFoam PUBLIC cxx_std_11)
target_link_libraries(buoyantBoussinesqPimpleFoam PUBLIC atmosphericModels)
target_include_directories(buoyantBoussinesqPimpleFoam PUBLIC
  .
)
