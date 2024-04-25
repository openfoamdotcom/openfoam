# Define this directory for furture include use.
set(OPENFOAM_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
  add_subdirectory(OSspecific/MSwindows)
else()
  add_subdirectory(OSspecific/POSIX)
endif()

if (MPI_FOUND)
  add_subdirectory(Pstream/mpi)
else()
  add_subdirectory(Pstream/dummy)
endif()

add_subdirectory(OpenFOAM)

add_subdirectory(fileFormats)
add_subdirectory(surfMesh)
add_subdirectory(meshTools)

add_subdirectory(finiteArea)
add_subdirectory(finiteVolume)

add_subdirectory(mesh/blockMesh)
add_subdirectory(mesh/extrudeModel)
add_subdirectory(dynamicMesh)
add_subdirectory(genericPatchFields)

add_subdirectory(parallel/decompose/decompositionMethods)
add_subdirectory(parallel/decompose/faDecompose)
if(METIS_FOUND)
  add_subdirectory(parallel/decompose/metisDecomp)
endif()
if(SCOTCH_FOUND)
  add_subdirectory(parallel/decompose/scotchDecomp)
endif()
if(PTSCOTCH_FOUND)
  add_subdirectory(parallel/decompose/ptscotchDecomp)
endif()
if(KAHIP_FOUND)
  add_subdirectory(parallel/decompose/kahipDecomp)
endif()

add_subdirectory(lagrangian/basic)
add_subdirectory(lagrangian/distributionModels)

add_subdirectory(parallel/decompose/decompose)

add_subdirectory(parallel/reconstruct/reconstruct)
add_subdirectory(parallel/reconstruct/faReconstruct)
add_subdirectory(parallel/distributed)

