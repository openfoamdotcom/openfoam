set(_FILES
  postChannel.C
  channelIndex.C
)
add_executable(postChannel ${_FILES})
target_compile_features(postChannel PUBLIC cxx_std_11)
target_link_libraries(postChannel PUBLIC genericPatchFields sampling)
target_include_directories(postChannel PUBLIC
  .
)
