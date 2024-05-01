set(_FILES
)
add_executable(Test-partition-sort ${_FILES})
target_compile_features(Test-partition-sort PUBLIC cxx_std_11)
