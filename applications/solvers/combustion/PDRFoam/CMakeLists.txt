set(_FILES
  XiModels/XiModel/XiModel.C
  XiModels/XiModel/XiModelNew.C
  XiModels/fixed/fixed.C
  XiModels/algebraic/algebraic.C
  XiModels/transport/transport.C
  XiModels/XiEqModels/XiEqModel/XiEqModel.C
  XiModels/XiEqModels/XiEqModel/XiEqModelNew.C
  XiModels/XiEqModels/Gulder/Gulder.C
  XiModels/XiEqModels/instabilityXiEq/instabilityXiEq.C
  XiModels/XiEqModels/SCOPEBlendXiEq/SCOPEBlendXiEq.C
  XiModels/XiEqModels/SCOPEXiEq/SCOPEXiEq.C
  XiModels/XiGModels/XiGModel/XiGModel.C
  XiModels/XiGModels/XiGModel/XiGModelNew.C
  XiModels/XiGModels/KTS/KTS.C
  XiModels/XiGModels/instabilityG/instabilityG.C
  PDRModels/turbulence/PDRkEpsilon/PDRkEpsilon.C
  PDRModels/dragModels/PDRDragModel/PDRDragModel.C
  PDRModels/dragModels/PDRDragModel/PDRDragModelNew.C
  PDRModels/dragModels/basic/basic.C
  PDRModels/XiEqModels/basicXiSubXiEq/basicXiSubXiEq.C
  PDRModels/XiGModels/basicXiSubG/basicXiSubG.C
  laminarFlameSpeed/SCOPE/SCOPELaminarFlameSpeed.C
  PDRFoam.C
)
add_executable(PDRFoam ${_FILES})
target_compile_features(PDRFoam PUBLIC cxx_std_11)
target_link_libraries(PDRFoam PUBLIC dynamicFvMesh engine laminarFlameSpeedModels thermoTools)
target_include_directories(PDRFoam PUBLIC
  .
)
