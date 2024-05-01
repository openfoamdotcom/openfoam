set(_FILES
  adjointOptimisationFoam.C
)
add_executable(adjointOptimisationFoam ${_FILES})
target_compile_features(adjointOptimisationFoam PUBLIC cxx_std_11)
target_link_libraries(adjointOptimisationFoam PUBLIC adjointOptimisation)
target_include_directories(adjointOptimisationFoam PUBLIC
  .
)
