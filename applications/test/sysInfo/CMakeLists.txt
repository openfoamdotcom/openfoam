set(_FILES
)
add_executable(Test-sysInfo ${_FILES})
target_compile_features(Test-sysInfo PUBLIC cxx_std_11)
