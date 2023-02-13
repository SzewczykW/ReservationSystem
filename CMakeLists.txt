# Setup the project
cmake_minimum_required (VERSION 3.1.0 FATAL_ERROR)
project (reservation_system)

# Set the C standard to C17
set(CMAKE_C_STANDARD 17 CACHE STRING "C standard to conform to is C17" FORCE)
set(CMAKE_C_STANDARD_REQUIRED ON CACHE BOOL "C17 standard is required" FORCE)
set(CMAKE_C_FLAGS "-O2" CACHE STRING "C flags" FORCE)

# for static library
set(CMAKE_POSITION_INDEPENDENT_CODE ON CACHE BOOL "Enable PIC" FORCE)

# preventing in-source building
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON CACHE BOOL "Disable in-source build" FORCE)
set(CMAKE_DISABLE_SOURCE_CHANGES ON CACHE BOOL "Disable source changes" FORCE)
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed")
endif()

# Set the output directories
add_definitions(-DDATAPATH=\"${PROJECT_SOURCE_DIR}/data\" -DDEBUG=1)    # for debug
add_compile_definitions("DEBUG=$<CONFIG:Debug>" "RELEASE=$<CONFIG:Release>")    # for Debug/Release
            
message(INFO " SOURCE_DIR: " ${LIB_SOURCE_DIR})   # for Debug/Release

set(LIB_SOURCE_DIR ${PROJECT_SOURCE_DIR}  CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

set(HEADERS_DIR "${LIB_SOURCE_DIR}/include/*.h" CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
file(GLOB SOURCES "${LIB_SOURCE_DIR}/src/*.c" CACHE INTERNAL "${PROJECT_NAME}: Include Sources" FORCE) 

include_directories(${HEADERS_DIR})

# Define the library
add_library(${PROJECT_NAME} STATIC ${SOURCES})

#----------------------------------------------------------------------------
# Expose project's public includes to other subprojects through cache variable.
set(${PROJECT_NAME} ${HEADERS_DIR} CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

add_definitions( ${reservation_system_DEFINITIONS} ) #add definitions from above to the target
include_directories(${reservation_system} ) #add include directories from above to the target


enable_testing() # enable testing

add_test(NAME Mem COMMAND valgrind --leak-check=full --track-origins=yes --error-exitcode=1 ./${PROJECT_NAME}) # add test


add_custom_target(info # ALL # target zoo is always built
    COMMAND echo "Build commands:" 
    COMMAND cat compile_commands.json  # print the compile commands
    COMMAND echo "" 
    COMMAND echo "" 
    COMMAND echo "Debug info:"  
    COMMAND readelf --debug-dump=decodedline reservation_system  # print the debug info 
    DEPENDS reservation_system # depends on target zoo
)

option(BUILD_DOXY_DOC "build doxygen documentation" ON) # option to build doxygen documentation
if(BUILD_DOXY_DOC) # if option is set to ON
    find_package(Doxygen REQUIRED dot) # find doxygen
    if(NOT DOXYGEN_FOUND) # if doxygen is not found
        message(WARNING "Doxygen not found, unable to generate documentation") # print warning
    else() # if doxygen is found
        set(DOXY_DOC_DEST_DIR ${CMAKE_BINARY_DIR} CACHE PATH "Path to the doxygen output")                      # used in the doxyfile.in
        set(DOXY_DOC_INPUT_ROOT_DIRS ${CMAKE_HOME_DIRECTORY} CACHE PATH "Path from where to start to parse")    # used in the doxyfile.in
        set(DOXY_DOC_EXCLUDE_PATTERNS_DIRS ${CMAKE_BINARY_DIR} CACHE STRING "Regex patterns exclusion")          # used in the doxyfile.in
        set(DOXY_DOC_COMMON_IMG_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Path from which doxygen will be able to found referenced images")# used in the doxyfile.in
        configure_file(doxyfile.in ${CMAKE_BINARY_DIR}/doxyfile @ONLY IMMEDIATE) # configure the doxyfile.in
        add_custom_target(doxyDoc COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/doxyfile" # add custom target to build the documentation
            WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY} # set the working directory
            COMMENT "Building user's documentation into doxyDoc build dir..." # print a message
        )
    endif()
endif()