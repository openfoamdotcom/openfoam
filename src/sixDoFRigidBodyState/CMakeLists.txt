set(_FILES
  sixDoFRigidBodyState.C
)
add_library(sixDoFRigidBodyState ${_FILES})
target_compile_features(sixDoFRigidBodyState PUBLIC cxx_std_11)
set_property(TARGET sixDoFRigidBodyState PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(sixDoFRigidBodyState PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(sixDoFRigidBodyState PUBLIC dynamicFvMesh sixDoFRigidBodyMotion)
target_include_directories(sixDoFRigidBodyState PUBLIC
  .
)
install(TARGETS sixDoFRigidBodyState DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
