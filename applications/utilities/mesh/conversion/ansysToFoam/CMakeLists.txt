set(_FILES
)
set(_flex_src ${CMAKE_CURRENT_BINARY_DIR}/ansysToFoam.C)
flex_target(MyFlexName ansysToFoam.L "${_flex_src}" COMPILE_FLAGS --c++)
add_executable(ansysToFoam ${_FILES})
target_compile_features(ansysToFoam PUBLIC cxx_std_11)
target_link_libraries(ansysToFoam PUBLIC finiteVolume)
