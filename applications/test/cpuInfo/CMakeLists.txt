set(_FILES
)
add_executable(Test-cpuInfo ${_FILES})
target_compile_features(Test-cpuInfo PUBLIC cxx_std_11)
