set(_FILES
  Kmesh/Kmesh.C
  fft/fft.C
  fft/calcEk.C
  fft/kShellIntegration.C
  processes/UOprocess/UOprocess.C
  turbulence/turbGen.C
  noise/noiseFFT/noiseFFT.C
  noise/noiseModels/noiseModel/noiseModel.C
  noise/noiseModels/noiseModel/noiseModelNew.C
  noise/noiseModels/pointNoise/pointNoise.C
  noise/noiseModels/surfaceNoise/surfaceNoise.C
  windowModels/windowModel/windowModel.C
  windowModels/windowModel/windowModelNew.C
  windowModels/Hanning/Hanning.C
  windowModels/uniform/uniform.C
)
add_library(randomProcesses ${_FILES})
target_compile_features(randomProcesses PUBLIC cxx_std_11)
target_compile_definitions(randomProcesses PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(randomProcesses PUBLIC sampling FFTW3::fftw3f)
target_include_directories(randomProcesses PUBLIC
  Kmesh
  fft
  noise/noiseFFT
  noise/noiseModels/noiseModel
  noise/noiseModels/pointNoise
  noise/noiseModels/surfaceNoise
  processes/UOprocess
  turbulence
  windowModels/Hanning
  windowModels/uniform
  windowModels/windowModel
)
install(TARGETS randomProcesses DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
