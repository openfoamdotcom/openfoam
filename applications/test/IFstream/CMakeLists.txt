set(_FILES
)
add_executable(Test-IFstream ${_FILES})
target_compile_features(Test-IFstream PUBLIC cxx_std_11)
target_link_libraries(Test-IFstream PUBLIC finiteVolume)
