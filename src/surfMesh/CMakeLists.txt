set(_FILES
  MeshedSurfaceAllocator/MeshedSurfaceIOAllocator.C
  MeshedSurface/MeshedSurfaceCore.C
  MeshedSurface/MeshedSurfaces.C
  UnsortedMeshedSurface/UnsortedMeshedSurfaces.C
  MeshedSurfaceProxy/MeshedSurfaceProxys.C
  mergedSurf/mergedSurf.C
  polySurface/polySurface.C
  polySurface/polySurfaceClear.C
  polySurface/polySurfaceIO.C
  polySurface/fields/polySurfaceFields.C
  surfaceRegistry/surfaceRegistry.C
  surfMesh/surfMesh.C
  surfMesh/surfMeshClear.C
  surfMesh/surfMeshIO.C
  surfMesh/fields/surfFields.C
  surfZone/surfZone.C
  surfZone/surfZoneIOList.C
  surfaceFormats/surfaceFormatsCore.C
  surfaceFormats/abaqus/ABAQUSsurfaceFormatCore.C
  surfaceFormats/abaqus/ABAQUSsurfaceFormatRunTime.C
  surfaceFormats/ac3d/AC3DsurfaceFormatCore.C
  surfaceFormats/ac3d/AC3DsurfaceFormatRunTime.C
  surfaceFormats/fire/FLMAsurfaceFormatRunTime.C
  surfaceFormats/gts/GTSsurfaceFormatRunTime.C
  surfaceFormats/gts/triSurfaceGTSformat.C
  surfaceFormats/nas/NASsurfaceFormatRunTime.C
  surfaceFormats/obj/OBJsurfaceFormatRunTime.C
  surfaceFormats/off/OFFsurfaceFormatRunTime.C
  surfaceFormats/smesh/SMESHsurfaceFormatRunTime.C
  surfaceFormats/starcd/STARCDsurfaceFormatCore.C
  surfaceFormats/starcd/STARCDsurfaceFormatRunTime.C
  surfaceFormats/stl/STLsurfaceFormatRunTime.C
  surfaceFormats/stl/triSurfaceSTLformat.C
  surfaceFormats/tri/TRIReader.C
  surfaceFormats/tri/TRIsurfaceFormatRunTime.C
  surfaceFormats/vtk/VTKsurfaceFormatCore.C
  surfaceFormats/vtk/VTKsurfaceFormatRunTime.C
  surfaceFormats/vtp/VTPsurfaceFormatCore.C
  surfaceFormats/vtp/VTPsurfaceFormatRunTime.C
  surfaceFormats/x3d/X3DsurfaceFormatCore.C
  surfaceFormats/x3d/X3DsurfaceFormatRunTime.C
  triSurface/triSurface.C
  triSurface/triSurfaceIO.C
  triSurface/triSurfaceNew.C
  triSurface/triSurfaceAddressing.C
  triSurface/triSurfaceStitch.C
  triSurface/fields/triSurfaceFields.C
  triSurface/patches/surfacePatch.C
  readers/common/surfaceReader.C
  readers/boundary/boundaryDataSurfaceReader.C
  readers/ensight/ensightSurfaceReader.C
  writers/common/surfaceWriter.C
  writers/abaqus/abaqusSurfaceWriter.C
  writers/boundary/boundaryDataSurfaceWriter.C
  writers/debug/debugSurfaceWriter.C
  writers/ensight/ensightSurfaceWriter.C
  writers/foam/foamSurfaceWriter.C
  writers/nastran/nastranSurfaceWriter.C
  writers/null/nullSurfaceWriter.C
  writers/proxy/proxySurfaceWriter.C
  writers/raw/rawSurfaceWriter.C
  writers/starcd/starcdSurfaceWriter.C
  writers/vtk/vtkSurfaceWriter.C
  writers/x3d/x3dSurfaceWriter.C
)
add_library(surfMesh ${_FILES})
target_compile_features(surfMesh PUBLIC cxx_std_11)
set_property(TARGET surfMesh PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(surfMesh PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(surfMesh PUBLIC fileFormats)
target_include_directories(surfMesh PUBLIC
  .
)
install(TARGETS surfMesh DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
