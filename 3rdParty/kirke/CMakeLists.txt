set( kirke__DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE STRING "The root directory for the kirke module." )

#[[
set( KIRKE_BUILD_TESTS OFF )
set( KIRKE_BUILD_COVERAGE_REPORT OFF )
set( KIRKE_BUILD_DOCUMENTATION OFF )
]]
add_subdirectory( ${kirke__DIR}/kirke )