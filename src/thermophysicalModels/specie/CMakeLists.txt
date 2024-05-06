set(_FILES
  atomicWeights/atomicWeights.C
  specie/specie.C
  reaction/reactions/makeReactions.C
  reaction/reactions/makeLangmuirHinshelwoodReactions.C
)
add_library(specie ${_FILES})
target_compile_features(specie PUBLIC cxx_std_11)
set_property(TARGET specie PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(specie PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
if (BUILD_SHARED_LIBS AND USING_CLANG)
  target_link_options(specie PUBLIC -undefined dynamic_lookup)
endif()
target_link_libraries(specie PUBLIC OpenFOAM)
target_include_directories(specie PUBLIC
  .
  PRIVATE
  ${OPENFOAM_SRC_DIR}/regionModels/pyrolysisModels
  ${OPENFOAM_SRC_DIR}/regionModels/regionModel
  ${OPENFOAM_SRC_DIR}/thermophysicalModels/chemistryModel
  ${OPENFOAM_SRC_DIR}/thermophysicalModels/radiation
  ${OPENFOAM_SRC_DIR}/thermophysicalModels/reactionThermo
  ${OPENFOAM_SRC_DIR}/thermophysicalModels/solidChemistryModel
  ${OPENFOAM_SRC_DIR}/thermophysicalModels/solidThermo
  ${OPENFOAM_SRC_DIR}/finiteVolume
  ${OPENFOAM_SRC_DIR}/meshTools
  ${OPENFOAM_SRC_DIR}/thermophysicalModels/basic
  ${OPENFOAM_SRC_DIR}/thermophysicalModels/thermophysicalProperties
  ${OPENFOAM_SRC_DIR}/transportModels/compressible
)
install(TARGETS specie DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
