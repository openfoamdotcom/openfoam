set(_FILES
  compressibleInterIsoFoam.C
)
add_executable(compressibleInterIsoFoam ${_FILES})
target_compile_features(compressibleInterIsoFoam PUBLIC cxx_std_11)
target_link_libraries(compressibleInterIsoFoam PUBLIC VoFphaseCompressibleTurbulenceModels dynamicFvMesh fvOptions geometricVoF twoPhaseSurfaceTension)
target_include_directories(compressibleInterIsoFoam PUBLIC
  .
)
