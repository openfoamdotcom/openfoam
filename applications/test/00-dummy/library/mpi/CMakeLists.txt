set(_FILES
)
add_library(TestDummyMpi ${_FILES})
target_compile_features(TestDummyMpi PUBLIC cxx_std_11)
set_property(TARGET TestDummyMpi PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(TestDummyMpi PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(TestDummyMpi PUBLIC
  .
)
install(TARGETS TestDummyMpi DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
