set(_FILES
)
add_executable(Test-OFstream ${_FILES})
target_compile_features(Test-OFstream PUBLIC cxx_std_11)
target_include_directories(Test-OFstream PUBLIC
  .
)
