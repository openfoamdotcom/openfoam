set(_FILES
  atomicWeights/atomicWeights.C
  specie/specie.C
  reaction/reactions/makeReactions.C
  reaction/reactions/makeLangmuirHinshelwoodReactions.C
)
add_library(specie ${_FILES})
target_compile_features(specie PUBLIC cxx_std_11)
target_compile_definitions(specie PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
if (BUILD_SHARED_LIBS AND USING_CLANG)
  target_link_options(specie PUBLIC -undefined dynamic_lookup)
endif()
target_link_libraries(specie PUBLIC OpenFOAM)
target_include_directories(specie PUBLIC
  .
  PRIVATE
  ${OPENFOAM_SRC_DIR}/thermophysicalModels/thermophysicalProperties
)
install(TARGETS specie DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
