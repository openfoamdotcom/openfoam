set(_FILES
)
add_executable(Test-OFstream ${_FILES})
target_compile_features(Test-OFstream PUBLIC cxx_std_11)
