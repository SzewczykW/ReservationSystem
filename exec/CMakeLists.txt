############################################################################################################

cmake_minimum_required ( VERSION 3.3.0 FATAL_ERROR )
project ( "Reservations.exe" )

############################################################################################################

add_definitions ( ${ReservationsLib_DEFINITIONS} )
include_directories ( ${ReservationsLib} )

############################################################################################################

# linking
add_executable ( ${PROJECT_NAME} main/Main.cpp )
target_link_libraries ( ${PROJECT_NAME} PRIVATE ReservationsLib )

############################################################################################################

# install Reservations.exe 
message ( STATUS "${PROJECT_NAME} will be installed to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
install ( TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )

############################################################################################################