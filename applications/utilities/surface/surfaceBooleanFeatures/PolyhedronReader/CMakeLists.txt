set(_FILES
  PolyhedronReader.C
)
add_library(PolyhedronReader ${_FILES})
target_compile_features(PolyhedronReader PUBLIC cxx_std_11)
set_property(TARGET PolyhedronReader PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(PolyhedronReader PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(PolyhedronReader PUBLIC meshTools)
target_include_directories(PolyhedronReader PUBLIC
  .
)
install(TARGETS PolyhedronReader DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
