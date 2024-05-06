set(_FILES
  potential/potential.C
  pairPotential/pairPotentialList/pairPotentialList.C
  pairPotential/basic/pairPotential.C
  pairPotential/basic/pairPotentialIO.C
  pairPotential/basic/pairPotentialNew.C
  pairPotential/derived/lennardJones/lennardJones.C
  pairPotential/derived/maitlandSmith/maitlandSmith.C
  pairPotential/derived/azizChen/azizChen.C
  pairPotential/derived/exponentialRepulsion/exponentialRepulsion.C
  pairPotential/derived/coulomb/coulomb.C
  pairPotential/derived/dampedCoulomb/dampedCoulomb.C
  pairPotential/derived/noInteraction/noInteraction.C
  energyScalingFunction/basic/energyScalingFunction.C
  energyScalingFunction/basic/energyScalingFunctionNew.C
  energyScalingFunction/derived/shifted/shifted.C
  energyScalingFunction/derived/shiftedForce/shiftedForce.C
  energyScalingFunction/derived/noScaling/noScaling.C
  energyScalingFunction/derived/sigmoid/sigmoid.C
  energyScalingFunction/derived/doubleSigmoid/doubleSigmoid.C
  tetherPotential/tetherPotentialList/tetherPotentialList.C
  tetherPotential/basic/tetherPotential.C
  tetherPotential/basic/tetherPotentialNew.C
  tetherPotential/derived/harmonicSpring/harmonicSpring.C
  tetherPotential/derived/restrainedHarmonicSpring/restrainedHarmonicSpring.C
  tetherPotential/derived/pitchForkRing/pitchForkRing.C
  electrostaticPotential/electrostaticPotential.C
)
add_library(potential ${_FILES})
target_compile_features(potential PUBLIC cxx_std_11)
set_property(TARGET potential PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(potential PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(potential PUBLIC finiteVolume)
target_include_directories(potential PUBLIC
  .
)
install(TARGETS potential DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
