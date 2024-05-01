set(_FILES
  Test-SpanStream1.C
)
add_executable(Test-SpanStream1 ${_FILES})
target_compile_features(Test-SpanStream1 PUBLIC cxx_std_11)
