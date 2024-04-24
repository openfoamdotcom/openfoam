set(_FILES
)
add_executable(Test-IOobject-type ${_FILES})
target_compile_features(Test-IOobject-type PUBLIC cxx_std_11)
target_link_libraries(Test-IOobject-type PUBLIC finiteVolume)
