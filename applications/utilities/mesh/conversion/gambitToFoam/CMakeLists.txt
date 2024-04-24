set(_FILES
)
set(_flex_src ${CMAKE_CURRENT_BINARY_DIR}/gambitToFoam.C)
flex_target(MyFlexName gambitToFoam.L "${_flex_src}" COMPILE_FLAGS --c++)
add_executable(gambitToFoam ${_FILES})
target_compile_features(gambitToFoam PUBLIC cxx_std_11)
target_link_libraries(gambitToFoam PUBLIC finiteVolume)
