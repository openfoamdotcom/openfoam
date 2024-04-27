set(_FILES
  SloanRenumber.C
)
add_library(SloanRenumber ${_FILES})
target_compile_features(SloanRenumber PUBLIC cxx_std_11)
target_compile_definitions(SloanRenumber PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(SloanRenumber PUBLIC renumberMethods)
target_include_directories(SloanRenumber PUBLIC
  .
)
install(TARGETS SloanRenumber DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
