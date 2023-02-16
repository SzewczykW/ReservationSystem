cmake_minimum_required (VERSION 3.1.0 FATAL_ERROR)

#
# Building
#

# Set the build type if none was specified
if (NOT CMAKE_BUILD_TYPE)
    message ("Setting build type to 'Release' as none was specified.")
    set (CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif ()
string (TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UPPER)
message (STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE_UPPER}")

# prevent in-source builds
set (CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set (CMAKE_DISABLE_SOURCE_CHANGES ON)
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message (FATAL_ERROR "In-source builds are not allowed.")
endif ()

add_definitions(-DPROJECTPATH=\"${PROJECT_SOURCE_DIR}\")

#
# Compiling
#

# Create the project
project ("ReservationSystem" VERSION 0.0.1 LANGUAGES C)

# C standard required by the project
set (CMAKE_C_STANDARD 17)
set (CMAKE_C_STANDARD_REQUIRED ON)
set (CMAKE_C_EXTENSIONS OFF) #No compiler specific extensions

# Selected flags don't work at compile time
if (MSVC)
    set (CMAKE_CC_FLAGS
        "${CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE_UPPER}}"                        # Build type specific flags
        "/W4"                                                               # All warnings
        "/WX"                                                               # Treat warnings as errors
        "/std:c17"                                                          # C standard
        )
else ()
    set (CMAKE_CC_FLAGS
        "${CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE_UPPER}}"                        # Build type specific flags
        "-Wall"                                                             # All warnings
        "-Wextra"                                                           # Extra warnings
        "-Wpedantic"                                                        # Pedantic warnings
        "-Werror"                                                           # Treat warnings as errors
        "-std=c17"                                                          # C standard
        )
endif ()

message (STATUS "CMAKE_CC_FLAGS: ${CMAKE_CC_FLAGS}")
message (STATUS "CMAKE_C_COMPILER is ${CMAKE_C_COMPILER}")
message (STATUS "CMAKE_C_COMPILER_VERSION is ${CMAKE_C_COMPILER_VERSION}")

# Set include directories
set (INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories (${INCLUDES})

# Set source directories
file (GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

# Generate shared library
add_library (${PROJECT_NAME}_library SHARED ${SOURCES})

target_include_directories (${PROJECT_NAME}_library PUBLIC ${INCLUDES})

#
# Linking
#

# Generate executable
add_executable (${PROJECT_NAME} ${SOURCES})

# Link the executable to the shared library
target_link_libraries (${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_library)

# Binaries
install (TARGETS ${PROJECT_NAME} DESTINATION bin)

#
# Testing
#

enable_testing ()

add_test (NAME Mem COMMAND valgrind --leak-check=full --track-origins=yes --error-exitcode=177 ./${PROJECT_NAME})

# test of program 


# generate compile_commands json file
add_custom_target (info # ALL # target zoo is always built
    COMMAND echo "Build commands:"
    COMMAND cat compile_commands.json  
    COMMAND echo "" 
    COMMAND echo ""
    COMMAND echo "Debug info:" 
    COMMAND readelf --debug-dump=decodedline ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
)

#
# Documentation
#

# documentation generation with doxygen

#option (BUILD_DOXY_DOC "build doxygen documentation" ON)
#if (BUILD_DOXY_DOC)
#    find_package (Doxygen REQUIRED dot)
#    if (NOT DOXYGEN_FOUND)
#        message (WARNING "Doxygen not found, unable to generate documentation")
#    else ()
#        set (DOXY_DOC_DEST_DIR ${CMAKE_BINARY_DIR} CACHE PATH "Path to the doxygen output")                      ## used in the doxyfile.in
#        set (DOXY_DOC_INPUT_ROOT_DIRS ${CMAKE_HOME_DIRECTORY} CACHE PATH "Path from where to start to parse")    ## used in the doxyfile.in
#        set (DOXY_DOC_EXCLUDE_PATTERNS_DIRS ${CMAKE_BINARY_DIR} CACHE STRING "Regex patterns exclusion")          ## used in the doxyfile.in
#        set (DOXY_DOC_COMMON_IMG_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Path from which doxygen will be able to found referenced images")## used in the doxyfile.in
#        configure_file (doxyfile.in ${CMAKE_BINARY_DIR}/doxyfile @ONLY)
#        add_custom_target (doxyDoc COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/doxyfile"
#            WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
#            COMMENT "Building user's documentation into doxyDoc build dir..."
#        )
#    endif ()
#endif ()