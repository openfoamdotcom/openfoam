cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(OpenFOAM_Third_Party LANGUAGES C CXX)

cmake_policy(SET CMP0057 NEW)
cmake_policy(SET CMP0054 NEW)

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

include(ExternalProject)

message(STATUS "ENV{OPENFOAM_THIRD_PARTY_ROOT}: $ENV{OPENFOAM_THIRD_PARTY_ROOT}")
message(STATUS "OPENFOAM_THIRD_PARTY_ROOT: ${OPENFOAM_THIRD_PARTY_ROOT}")
message(STATUS "TP_ROOT: ${TP_ROOT}")
if (DEFINED ENV{OPENFOAM_THIRD_PARTY_ROOT})
  set(TP_ROOT "$ENV{OPENFOAM_THIRD_PARTY_ROOT}")
elseif (DEFINED OPENFOAM_THIRD_PARTY_ROOT)
  set(TP_ROOT "${OPENFOAM_THIRD_PARTY_ROOT}")
else()
  set(TP_ROOT ${TP_ROOT})
endif()

if (NOT IS_DIRECTORY "${TP_ROOT}")
  message(FATAL_ERROR "\nDie!\n - Third party root is not a directory: ${TP_ROOT}\n")
endif()

if (APPLE)
  set(_PRE_BISON_CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}")
  set(CMAKE_PREFIX_PATH)
  file(GLOB children /usr/local/Cellar/bison/*)
  foreach(child ${children})
    list(APPEND CMAKE_PREFIX_PATH ${child}/bin)
  endforeach()
endif()

find_package(BISON 3)

if (APPLE)
  set(CMAKE_PREFIX_PATH "${_PRE_BISON_CMAKE_PREFIX_PATH}")
endif()

ExternalProject_Add(GKlib
    GIT_REPOSITORY https://github.com/openfoamdotcom/GKlib.git
    GIT_TAG main
    SOURCE_DIR "${TP_ROOT}/src/GKlib"
    BINARY_DIR "${TP_ROOT}/build/GKlib"
    CMAKE_COMMAND ${CMAKE_COMMAND}
    CMAKE_ARGS -DGKLIB_TESTS=OFF -DGKLIB_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${TP_ROOT}/install
)

ExternalProject_Add(fftw
  URL https://fftw.org/fftw-3.3.10.tar.gz
  URL_MD5 8ccbf6a5ea78a16dbc3e1306e234cc5c
  SOURCE_DIR "${TP_ROOT}/src/fftw"
  BINARY_DIR "${TP_ROOT}/build/fftw"
  CMAKE_COMMAND ${CMAKE_COMMAND}
  CMAKE_ARGS -DENABLE_AVX=ON -DENABLE_AVX2=ON -DENABLE_FLOAT=ON -DENABLE_SSE=ON -DENABLE_SSE2=ON -DENABLE_THREADS=ON -DBUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${TP_ROOT}/install
)

ExternalProject_Add(metis
  GIT_REPOSITORY https://github.com/openfoamdotcom/METIS.git
  GIT_TAG main
  SOURCE_DIR "${TP_ROOT}/src/metis"
  BINARY_DIR "${TP_ROOT}/build/metis"
  CMAKE_COMMAND ${CMAKE_COMMAND}
  CMAKE_ARGS -DMETIS_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${TP_ROOT}/install
  DEPENDS GKlib
)

if (BISON_FOUND)
  ExternalProject_Add(scotch
    GIT_REPOSITORY https://gitlab.inria.fr/scotch/scotch.git
    GIT_TAG v7.0.4
    SOURCE_DIR "${TP_ROOT}/src/scotch"
    BINARY_DIR "${TP_ROOT}/build/scotch"
    CMAKE_COMMAND ${CMAKE_COMMAND}
    CMAKE_ARGS -DINSTALL_METIS_HEADERS=OFF -DBISON_EXECUTABLE=${BISON_EXECUTABLE} -DBUILD_LIBSCOTCHMETIS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${TP_ROOT}/install
  )
endif()

