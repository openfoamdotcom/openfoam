set(_FILES
  setSet.C
)
add_executable(setSet ${_FILES})
target_compile_features(setSet PUBLIC cxx_std_11)
target_link_libraries(setSet PUBLIC meshTools)
