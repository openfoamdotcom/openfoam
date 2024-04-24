set(_FILES
  reaction/reactions/makeSolidReactions.C
)
add_library(solidSpecie ${_FILES})
target_compile_features(solidSpecie PUBLIC cxx_std_11)
target_compile_definitions(solidSpecie PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(solidSpecie PUBLIC 
  include
  reaction/reactionRate/solidIsothermalReactionRate
  reaction/reactionRate/solidArrheniusReactionRate
  reaction/reactions
  reaction/ReactionsCaseDir/solidReaction
  transport/exponential
  transport/tabulated
  transport/const
  transport/polynomial
  include
)
install(TARGETS solidSpecie DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
