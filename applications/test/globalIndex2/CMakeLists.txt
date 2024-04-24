set(_FILES
)
add_executable(Test-globalIndex2 ${_FILES})
target_compile_features(Test-globalIndex2 PUBLIC cxx_std_11)
target_link_libraries(Test-globalIndex2 PUBLIC finiteVolume)
