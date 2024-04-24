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

