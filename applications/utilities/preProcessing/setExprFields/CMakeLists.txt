set(_FILES
  setExprFields.C
)
add_executable(setExprFields ${_FILES})
target_compile_features(setExprFields PUBLIC cxx_std_11)
target_link_libraries(setExprFields PUBLIC finiteVolume)
