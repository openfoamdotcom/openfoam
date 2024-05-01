set(_FILES
)
add_executable(Test-sliceRange ${_FILES})
target_compile_features(Test-sliceRange PUBLIC cxx_std_11)
