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
target_include_directories(waveModels PUBLIC 
  fvOptions/multiphaseMangrovesSource
  fvOptions/multiphaseMangrovesTurbulenceModel
  derivedFvPatchFields/waveAlpha
  derivedFvPatchFields/waveVelocity
  waveAbsorptionModels/derived/shallowWaterAbsorption
  waveAbsorptionModels/base/waveAbsorptionModel
  waveGenerationModels/derived/Boussinesq
  waveGenerationModels/derived/McCowan
  waveGenerationModels/derived/StokesI
  waveGenerationModels/derived/streamFunction
  waveGenerationModels/derived/irregularMultiDirectional
  waveGenerationModels/derived/cnoidal
  waveGenerationModels/derived/Grimshaw
  waveGenerationModels/derived/StokesII
  waveGenerationModels/derived/StokesV
  waveGenerationModels/base/regularWaveModel
  waveGenerationModels/base/irregularWaveModel
  waveGenerationModels/base/solitaryWaveModel
  waveGenerationModels/base/waveGenerationModel
  derivedPointPatchFields/waveMaker
  waveModel
)
install(TARGETS waveModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
