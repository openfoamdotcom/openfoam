set(_FILES
  objToVTK.C
)
add_executable(objToVTK ${_FILES})
target_compile_features(objToVTK PUBLIC cxx_std_11)
