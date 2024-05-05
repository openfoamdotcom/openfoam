set(_FILES
  reaction/reactions/makeSolidReactions.C
)
add_library(solidSpecie ${_FILES})
target_compile_features(solidSpecie PUBLIC cxx_std_11)
target_compile_definitions(solidSpecie PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(solidSpecie PUBLIC specie)
target_include_directories(solidSpecie PUBLIC
  .
)
install(TARGETS solidSpecie DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
