set(_FILES
)
add_executable(ansysToFoam ${_FILES})
target_compile_features(ansysToFoam PUBLIC cxx_std_11)
target_link_libraries(ansysToFoam PUBLIC finiteVolume)
