set(_FILES
  helpType/helpType.C
  helpType/helpTypeNew.C
  helpBoundary/helpBoundary.C
  helpFunctionObject/helpFunctionObject.C
  helpSolver/helpSolver.C
  doxygenXmlParser/doxygenXmlParser.C
)
add_library(helpTypes ${_FILES})
target_compile_features(helpTypes PUBLIC cxx_std_11)
set_property(TARGET helpTypes PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(helpTypes PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(helpTypes PUBLIC fluidThermophysicalModels incompressibleTurbulenceModels radiationModels thermoTools)
target_include_directories(helpTypes PUBLIC
  .
)
install(TARGETS helpTypes DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
