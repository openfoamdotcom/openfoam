set(_FILES
  phaseModel/phaseModel.C
  multiphaseSystem/multiphaseSystem.C
  diameterModels/diameterModel/diameterModel.C
  diameterModels/constantDiameter/constantDiameter.C
  diameterModels/isothermalDiameter/isothermalDiameter.C
  interfacialModels/dragModels/dragModel/dragModel.C
  interfacialModels/dragModels/Ergun/Ergun.C
  interfacialModels/dragModels/GidaspowErgunWenYu/GidaspowErgunWenYu.C
  interfacialModels/dragModels/GidaspowSchillerNaumann/GidaspowSchillerNaumann.C
  interfacialModels/dragModels/SchillerNaumann/SchillerNaumann.C
  interfacialModels/dragModels/Gibilaro/Gibilaro.C
  interfacialModels/dragModels/WenYu/WenYu.C
  interfacialModels/dragModels/SyamlalOBrien/SyamlalOBrien.C
  interfacialModels/dragModels/blended/blended.C
  interfacialModels/dragModels/interface/interface.C
  interfacialModels/heatTransferModels/heatTransferModel/heatTransferModel.C
  interfacialModels/heatTransferModels/RanzMarshall/RanzMarshall.C
  derivedFvPatchFields/alphaContactAngle/alphaContactAngleFvPatchScalarField.C
)
add_library(multiphaseSystem ${_FILES})
target_compile_features(multiphaseSystem PUBLIC cxx_std_11)
target_compile_definitions(multiphaseSystem PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(multiphaseSystem PUBLIC interfaceProperties incompressibleTransportModels)
target_include_directories(multiphaseSystem PUBLIC
  derivedFvPatchFields/alphaContactAngle
  diameterModels/constantDiameter
  diameterModels/diameterModel
  diameterModels/isothermalDiameter
  interfacialModels/dragModels/Ergun
  interfacialModels/dragModels/Gibilaro
  interfacialModels/dragModels/GidaspowErgunWenYu
  interfacialModels/dragModels/GidaspowSchillerNaumann
  interfacialModels/dragModels/SchillerNaumann
  interfacialModels/dragModels/SyamlalOBrien
  interfacialModels/dragModels/WenYu
  interfacialModels/dragModels/blended
  interfacialModels/dragModels/dragModel
  interfacialModels/dragModels/interface
  interfacialModels/heatTransferModels/RanzMarshall
  interfacialModels/heatTransferModels/heatTransferModel
  multiphaseSystem
  phaseModel
)
install(TARGETS multiphaseSystem DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
