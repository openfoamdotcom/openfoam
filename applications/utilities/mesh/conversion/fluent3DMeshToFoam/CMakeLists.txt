set(_FILES
)
set(_flex_src ${CMAKE_CURRENT_BINARY_DIR}/fluent3DMeshToFoam.C)
flex_target(MyFlexName fluent3DMeshToFoam.L "${_flex_src}" COMPILE_FLAGS --c++)
add_executable(fluent3DMeshToFoam ${_FILES})
target_compile_features(fluent3DMeshToFoam PUBLIC cxx_std_11)
target_link_libraries(fluent3DMeshToFoam PUBLIC finiteVolume)
