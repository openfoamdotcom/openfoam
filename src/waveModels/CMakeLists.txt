set(_FILES
  waveModel/waveModel.C
  waveModel/waveModelNew.C
  waveGenerationModels/base/waveGenerationModel/waveGenerationModel.C
  waveGenerationModels/base/irregularWaveModel/irregularWaveModel.C
  waveGenerationModels/base/regularWaveModel/regularWaveModel.C
  waveGenerationModels/base/solitaryWaveModel/solitaryWaveModel.C
  waveGenerationModels/derived/Boussinesq/BoussinesqWaveModel.C
  waveGenerationModels/derived/cnoidal/cnoidalWaveModel.C
  waveGenerationModels/derived/Grimshaw/GrimshawWaveModel.C
  waveGenerationModels/derived/McCowan/McCowanWaveModel.C
  waveGenerationModels/derived/streamFunction/streamFunctionWaveModel.C
  waveGenerationModels/derived/StokesII/StokesIIWaveModel.C
  waveGenerationModels/derived/StokesI/StokesIWaveModel.C
  waveGenerationModels/derived/StokesV/StokesVWaveModel.C
  waveGenerationModels/derived/irregularMultiDirectional/irregularMultiDirectionalWaveModel.C
  waveAbsorptionModels/base/waveAbsorptionModel/waveAbsorptionModel.C
  waveAbsorptionModels/derived/shallowWaterAbsorption/shallowWaterAbsorption.C
  derivedFvPatchFields/waveVelocity/waveVelocityFvPatchVectorField.C
  derivedFvPatchFields/waveAlpha/waveAlphaFvPatchScalarField.C
  derivedPointPatchFields/waveMaker/waveMakerPointPatchVectorField.C
  fvOptions/multiphaseMangrovesSource/multiphaseMangrovesSource.C
  fvOptions/multiphaseMangrovesTurbulenceModel/multiphaseMangrovesTurbulenceModel.C
)
add_library(waveModels ${_FILES})
target_compile_features(waveModels PUBLIC cxx_std_11)
target_compile_definitions(waveModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(waveModels PUBLIC fvOptions)
target_include_directories(waveModels PUBLIC
  derivedFvPatchFields/waveAlpha
  derivedFvPatchFields/waveVelocity
  derivedPointPatchFields/waveMaker
  fvOptions/multiphaseMangrovesSource
  fvOptions/multiphaseMangrovesTurbulenceModel
  waveAbsorptionModels/base/waveAbsorptionModel
  waveAbsorptionModels/derived/shallowWaterAbsorption
  waveGenerationModels/base/irregularWaveModel
  waveGenerationModels/base/regularWaveModel
  waveGenerationModels/base/solitaryWaveModel
  waveGenerationModels/base/waveGenerationModel
  waveGenerationModels/derived/Boussinesq
  waveGenerationModels/derived/Grimshaw
  waveGenerationModels/derived/McCowan
  waveGenerationModels/derived/StokesI
  waveGenerationModels/derived/StokesII
  waveGenerationModels/derived/StokesV
  waveGenerationModels/derived/cnoidal
  waveGenerationModels/derived/irregularMultiDirectional
  waveGenerationModels/derived/streamFunction
  waveModel
)
install(TARGETS waveModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
