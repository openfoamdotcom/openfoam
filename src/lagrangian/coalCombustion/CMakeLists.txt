set(_FILES
  coalParcel/makeCoalParcelSubmodels.C
  coalCloudList/coalCloudList.C
)
add_library(coalCombustion ${_FILES})
target_compile_features(coalCombustion PUBLIC cxx_std_11)
target_compile_definitions(coalCombustion PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(coalCombustion PUBLIC lagrangianTurbulence surfaceFilmModels dynamicFvMesh regionFaModels finiteArea)
target_include_directories(coalCombustion PUBLIC
  include
  submodels/surfaceReactionModel/COxidationDiffusionLimitedRate
  submodels/surfaceReactionModel/COxidationMurphyShaddix
  submodels/surfaceReactionModel/COxidationKineticDiffusionLimitedRate
  submodels/surfaceReactionModel/COxidationIntrinsicRate
  submodels/surfaceReactionModel/COxidationHurtMitchell
  coalCloudList
  include
  coalCloud
  coalParcel
)
install(TARGETS coalCombustion DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
