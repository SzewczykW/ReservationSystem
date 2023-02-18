############################################################################################################

cmake_minimum_required ( VERSION 3.3.0 FATAL_ERROR )
project ( "ReservationsLib" )

add_definitions( ${ReservationSystem_DEFINITIONS} )

############################################################################################################

set ( HEADERS_DIR ${PROJECT_SOURCE_DIR}/include )
file ( GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp )

include_directories ( ${HEADERS_DIR} )

# Create Shared library
add_library ( ${PROJECT_NAME} SHARED ${SOURCES} )

############################################################################################################

# Install libraries
message ( STATUS "${PROJECT_NAME} will be installed to ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}" )
install ( TARGETS ${PROJECT_NAME} 
          LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} 
          ARCHIVE DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

############################################################################################################

# Expose project's public includes to other subprojects
set ( ${PROJECT_NAME} ${HEADERS_DIR} CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE )

############################################################################################################