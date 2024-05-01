set(_FILES
  engineSwirl.C
)
add_executable(engineSwirl ${_FILES})
target_compile_features(engineSwirl PUBLIC cxx_std_11)
target_link_libraries(engineSwirl PUBLIC genericPatchFields)
target_include_directories(engineSwirl PUBLIC
  .
)
