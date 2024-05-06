set(_FILES
  reaction/reactions/makeSolidReactions.C
)
add_library(solidSpecie ${_FILES})
target_compile_features(solidSpecie PUBLIC cxx_std_11)
set_property(TARGET solidSpecie PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(solidSpecie PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(solidSpecie PUBLIC specie)
target_include_directories(solidSpecie PUBLIC
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
install(TARGETS solidSpecie DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
