set(_FILES
  ROMmodels/ROMmodel/ROMmodel.C
  ROMmodels/ROMmodel/ROMmodelNew.C
  ROMmodels/DMD/DMD.C
  createROMfields.C
)
add_executable(createROMfields ${_FILES})
target_compile_features(createROMfields PUBLIC cxx_std_11)
target_link_libraries(createROMfields PUBLIC finiteVolume)
