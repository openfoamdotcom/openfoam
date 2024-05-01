set(_FILES
  setExprBoundaryFields.C
)
add_executable(setExprBoundaryFields ${_FILES})
target_compile_features(setExprBoundaryFields PUBLIC cxx_std_11)
target_link_libraries(setExprBoundaryFields PUBLIC genericPatchFields)
target_include_directories(setExprBoundaryFields PUBLIC
  .
)
