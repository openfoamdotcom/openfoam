set(_FILES
  wallFunctionTable.C
)
add_executable(wallFunctionTable ${_FILES})
target_compile_features(wallFunctionTable PUBLIC cxx_std_11)
target_link_libraries(wallFunctionTable PUBLIC tabulatedWallFunctions)
