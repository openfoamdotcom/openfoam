set(_FILES
)
add_executable(Test-globalIndex1 ${_FILES})
target_compile_features(Test-globalIndex1 PUBLIC cxx_std_11)
target_link_libraries(Test-globalIndex1 PUBLIC finiteVolume)
