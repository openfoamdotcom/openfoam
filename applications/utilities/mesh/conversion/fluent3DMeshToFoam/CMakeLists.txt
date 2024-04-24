set(_FILES
)
add_executable(fluent3DMeshToFoam ${_FILES})
target_compile_features(fluent3DMeshToFoam PUBLIC cxx_std_11)
target_link_libraries(fluent3DMeshToFoam PUBLIC finiteVolume)
