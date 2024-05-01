set(_FILES
  simpleCoalParcelFoam.C
)
add_executable(simpleCoalParcelFoam ${_FILES})
target_compile_features(simpleCoalParcelFoam PUBLIC cxx_std_11)
target_link_libraries(simpleCoalParcelFoam PUBLIC coalCombustion faOptions fvOptions regionFaModels)
target_include_directories(simpleCoalParcelFoam PUBLIC
  .
)
