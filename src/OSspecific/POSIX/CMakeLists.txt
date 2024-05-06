set(_FILES
  POSIX.C
  cpuInfo/cpuInfo.C
  cpuTime/cpuTimePosix.C
  memInfo/memInfo.C
  signals/sigFpe.C
  signals/sigSegv.C
  signals/sigInt.C
  signals/sigQuit.C
  signals/sigStopAtWriteNow.C
  signals/sigWriteNow.C
  signals/timer.C
  regExp/regExpPosix.C
  fileStat/fileStat.C
  fileMonitor/fileMonitor.C
  printStack/printStack.C
)
add_library(OSspecific ${_FILES})
target_compile_features(OSspecific PUBLIC cxx_std_11)
set_property(TARGET OSspecific PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(OSspecific PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
if (BUILD_SHARED_LIBS AND USING_CLANG)
  target_link_options(OSspecific PUBLIC -undefined dynamic_lookup)
endif()
target_include_directories(OSspecific PUBLIC
  .
  PRIVATE
  ${OPENFOAM_SRC_DIR}/OpenFOAM
)
install(TARGETS OSspecific DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
