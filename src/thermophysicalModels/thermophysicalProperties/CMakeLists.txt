set(_FILES
  thermophysicalFunctions/thermophysicalFunction/thermophysicalFunction.C
  thermophysicalFunctions/NSRDSfunctions/NSRDSfunc0/NSRDSfunc0.C
  thermophysicalFunctions/NSRDSfunctions/NSRDSfunc1/NSRDSfunc1.C
  thermophysicalFunctions/NSRDSfunctions/NSRDSfunc2/NSRDSfunc2.C
  thermophysicalFunctions/NSRDSfunctions/NSRDSfunc3/NSRDSfunc3.C
  thermophysicalFunctions/NSRDSfunctions/NSRDSfunc4/NSRDSfunc4.C
  thermophysicalFunctions/NSRDSfunctions/NSRDSfunc5/NSRDSfunc5.C
  thermophysicalFunctions/NSRDSfunctions/NSRDSfunc6/NSRDSfunc6.C
  thermophysicalFunctions/NSRDSfunctions/NSRDSfunc7/NSRDSfunc7.C
  thermophysicalFunctions/NSRDSfunctions/NSRDSfunc14/NSRDSfunc14.C
  thermophysicalFunctions/APIfunctions/APIdiffCoefFunc/APIdiffCoefFunc.C
  thermophysicalFunctions/nonUniformTable/nonUniformTableThermophysicalFunction.C
  thermophysicalFunctions/integratedNonUniformTable/integratedNonUniformTableThermophysicalFunction.C
  thermophysicalProperties/thermophysicalProperties.C
  liquidProperties/liquidProperties/liquidProperties.C
  liquidProperties/liquidMixtureProperties/liquidMixtureProperties.C
  liquidProperties/liquid/liquid.C
  liquidProperties/H2O/H2O.C
  liquidProperties/C7H16/C7H16.C
  liquidProperties/C12H26/C12H26.C
  liquidProperties/C10H22/C10H22.C
  liquidProperties/C8H18/C8H18.C
  liquidProperties/IC8H18/IC8H18.C
  liquidProperties/C4H10O/C4H10O.C
  liquidProperties/C2H6O/C2H6O.C
  liquidProperties/IDEA/IDEA.C
  liquidProperties/aC10H7CH3/aC10H7CH3.C
  liquidProperties/bC10H7CH3/bC10H7CH3.C
  liquidProperties/C8H10/C8H10.C
  liquidProperties/C16H34/C16H34.C
  liquidProperties/C9H20/C9H20.C
  liquidProperties/C6H6/C6H6.C
  liquidProperties/C7H8/C7H8.C
  liquidProperties/C6H14/C6H14.C
  liquidProperties/C13H28/C13H28.C
  liquidProperties/C14H30/C14H30.C
  liquidProperties/C3H8/C3H8.C
  liquidProperties/C3H6O/C3H6O.C
  liquidProperties/C2H6/C2H6.C
  liquidProperties/CH3OH/CH3OH.C
  liquidProperties/C2H5OH/C2H5OH.C
  liquidProperties/Ar/Ar.C
  liquidProperties/N2/N2.C
  liquidProperties/MB/MB.C
  liquidProperties/CH4N2O/CH4N2O.C
  liquidProperties/nC3H8O/nC3H8O.C
  liquidProperties/iC3H8O/iC3H8O.C
  solidProperties/solidProperties/solidProperties.C
  solidProperties/solidProperties/solidPropertiesNew.C
  solidProperties/solidMixtureProperties/solidMixtureProperties.C
  solidProperties/ash/ash.C
  solidProperties/C/C.C
  solidProperties/CaCO3/CaCO3.C
)
add_library(thermophysicalProperties ${_FILES})
target_compile_features(thermophysicalProperties PUBLIC cxx_std_11)
set_property(TARGET thermophysicalProperties PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(thermophysicalProperties PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(thermophysicalProperties PUBLIC specie)
target_include_directories(thermophysicalProperties PUBLIC
  .
)
install(TARGETS thermophysicalProperties DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
