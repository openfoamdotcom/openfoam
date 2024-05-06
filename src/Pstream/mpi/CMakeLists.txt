set(_FILES
  PstreamGlobals.C
  UPstream.C
  UPstreamAllToAll.C
  UPstreamBroadcast.C
  UPstreamGatherScatter.C
  UPstreamReduce.C
  UPstreamRequest.C
  UIPstreamRead.C
  UOPstreamWrite.C
  UIPBstreamRead.C
  UOPBstreamWrite.C
)
add_library(Pstream ${_FILES})
target_compile_features(Pstream PUBLIC cxx_std_11)
set_property(TARGET Pstream PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(Pstream PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
if (BUILD_SHARED_LIBS AND USING_CLANG)
  target_link_options(Pstream PUBLIC -undefined dynamic_lookup)
endif()
target_link_libraries(Pstream PUBLIC MPI::MPI_CXX OSspecific)
target_include_directories(Pstream PUBLIC
  .
  PRIVATE
  ${OPENFOAM_SRC_DIR}/OpenFOAM
)
install(TARGETS Pstream DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
