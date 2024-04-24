set(_FILES
)
add_executable(gambitToFoam ${_FILES})
target_compile_features(gambitToFoam PUBLIC cxx_std_11)
target_link_libraries(gambitToFoam PUBLIC finiteVolume)
