############################################################################################################

cmake_minimum_required ( VERSION 3.3.0 FATAL_ERROR )

############################################################################################################

set ( CMAKE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Root directory of the project" )

# Set the output directory for the executables and libraries
# The destination of install is set to the build directory to avoid permission issues and to not pollute the system binary directories
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

message( STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" )
message( STATUS "CMAKE_LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}" )

############################################################################################################

# Set the build type if none was specified
if ( NOT CMAKE_BUILD_TYPE )
    message ( STATUS "Setting build type to 'Release' as none was specified." )
    set ( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE )
    # Set the possible values of build type for cmake-gui
    set_property ( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel" )
endif ()
string ( TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UPPER )
message ( STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE_UPPER}" )

# prevent in-source builds
set ( CMAKE_DISABLE_IN_SOURCE_BUILD ON )
set ( CMAKE_DISABLE_SOURCE_CHANGES ON )
if ( "${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}" )
  message ( FATAL_ERROR "In-source builds are not allowed." )
endif ()

############################################################################################################

# Create the project
project ( "ReservationSystem" VERSION 0.0.1 LANGUAGES C CXX )

############################################################################################################

# C++ standard required by the project
set ( CMAKE_CXX_STANDARD 17 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS OFF ) #No compiler specific extensions

############################################################################################################

# C compiler flags configuration checks
include ( CheckCCompilerFlag )

# C++ compiler flags configuration checks
include ( CheckCXXCompilerFlag )

# Set WARN_CXX_FLAGS
set ( WARN_CXX_FLAGS "" )

# Set the list of flags depending on the compiler
if ( MSVC )
    set ( WARN_CXX_FLAGS_TO_CHECK
        "/W4"                                                               # All warnings
        "/WX"                                                               # Treat warnings as errors                                                         
        )
else () # Assume GCC or Clang                               
    set ( WARN_CXX_FLAGS_TO_CHECK                    
        "-Wall"                                                             # All warnings
        "-Wextra"                                                           # Extra warnings
        "-Wpedantic"                                                        # Pedantic warnings
        "-Werror"                                                           # Treat warnings as errors
        "-Wcast-align"                                                      # Warn for potential performance problem casts
        "-Wcast-qual"                                                       # Warn for casts discarding qualifiers
        )
endif ()

# Add build type flags to the list of flags to check
set ( BUILD_TYPE_FLAGS "${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UPPER}}" )
string ( REPLACE " " ";" BUILD_TYPE_FLAGS_LIST ${BUILD_TYPE_FLAGS} )
set ( WARN_CXX_FLAGS_TO_CHECK_LIST "${WARN_CXX_FLAGS_TO_CHECK};${BUILD_TYPE_FLAGS_LIST}" )

# Check if the compiler supports the flags
foreach ( FLAG ${WARN_CXX_FLAGS_TO_CHECK_LIST} )
    # Remove [+-=] signs from the flag
    string( REGEX REPLACE "[-=+]" "" FLAG_NO_SIGNS ${FLAG} )
    # Check if the flag is supported by the compiler
    CHECK_CXX_COMPILER_FLAG ( ${FLAG} CXX_COMPILER_SUPPORTS_${FLAG_NO_SIGNS} )
    # If so add it to the list of warning flags
    if ( CXX_COMPILER_SUPPORTS_${FLAG_NO_SIGNS} )
        set ( WARN_CXX_FLAGS "${WARN_CXX_FLAGS} ${FLAG}" )
    endif ()
endforeach ()

# Set CMAKE_CXX_FLAGS and CMAKE_C_FLAGS
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_CXX_FLAGS}" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WARN_CXX_FLAGS}" )

############################################################################################################

if( CMAKE_CXX_COMPILER_LOADED AND CMAKE_C_COMPILER_LOADED )
    message ( STATUS "C++ Compiler is loaded" )
    message ( STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}" )
    message ( STATUS "CMAKE_CXX_COMPILER_ID is ${CMAKE_CXX_COMPILER_ID}" )
    message ( STATUS "CMAKE_CXX_COMPILER is ${CMAKE_CXX_COMPILER}" )
    message ( STATUS "CMAKE_CXX_COMPILER_VERSION is ${CMAKE_CXX_COMPILER_VERSION}" )
    message ( STATUS "C Compiler is loaded" )
    message ( STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}" )
    message ( STATUS "CMAKE_C_COMPILER_ID is ${CMAKE_C_COMPILER_ID}" )
    message ( STATUS "CMAKE_C_COMPILER is ${CMAKE_C_COMPILER}" )
    message ( STATUS "CMAKE_C_COMPILER_VERSION is ${CMAKE_C_COMPILER_VERSION}" )
elseif ( CMAKE_CXX_COMPILER_LOADED )
    message ( FATAL_ERROR "C Compiler is not loaded [FATAL ERROR]" )
else ()
    message ( FATAL_ERROR "C++ Compiler is not loaded [FATAL ERROR]" )
endif ()

############################################################################################################

add_subdirectory ( lib )
add_subdirectory ( exec )
add_subdirectory ( data )
#add_subdirectory ( test )
#add_subdirectory ( doc )

############################################################################################################
