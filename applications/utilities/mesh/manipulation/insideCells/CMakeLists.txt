set(_FILES
  insideCells.C
)
add_executable(insideCells ${_FILES})
target_compile_features(insideCells PUBLIC cxx_std_11)
target_link_libraries(insideCells PUBLIC meshTools)
