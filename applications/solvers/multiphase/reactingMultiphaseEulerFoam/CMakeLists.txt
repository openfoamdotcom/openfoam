set(_FILES
  reactingMultiphaseEulerFoam.C
)
add_executable(reactingMultiphaseEulerFoam ${_FILES})
target_compile_features(reactingMultiphaseEulerFoam PUBLIC cxx_std_11)
target_link_libraries(reactingMultiphaseEulerFoam PUBLIC fvOptions reactingMultiphaseSystem sampling)
target_include_directories(reactingMultiphaseEulerFoam PUBLIC
  .
)
