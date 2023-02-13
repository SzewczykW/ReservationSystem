cmake_minimum_required (VERSION 3.1.0)

project (out)

# prevent for in-source building
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

add_definitions(-DPROJECTPATH=\"${PROJECT_SOURCE_DIR}\")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDES})

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(INCLUDES_TEST)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLIB_TEST")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2")

add_executable(${PROJECT_NAME} main.c ${SOURCES})

enable_testing()

add_test(NAME Mem COMMAND valgrind --leak-check=full --track-origins=yes --error-exitcode=1 ./${PROJECT_NAME})


add_custom_target(info # ALL # target zoo is always built
    COMMAND echo "Build commands:"
    COMMAND cat compile_commands.json 
    COMMAND echo ""
    COMMAND echo ""
    COMMAND echo "Debug info:"
    COMMAND readelf --debug-dump=decodedline out
    DEPENDS out
)

#option(BUILD_DOXY_DOC "build doxygen documentation" ON)
#if(BUILD_DOXY_DOC)
#    find_package(Doxygen REQUIRED dot)
#    if(NOT DOXYGEN_FOUND)
#        message(WARNING "Doxygen not found, unable to generate documentation")
#    else()
#        set(DOXY_DOC_DEST_DIR ${CMAKE_BINARY_DIR} CACHE PATH "Path to the doxygen output")                      ## used in the doxyfile.in
#        set(DOXY_DOC_INPUT_ROOT_DIRS ${CMAKE_HOME_DIRECTORY} CACHE PATH "Path from where to start to parse")    ## used in the doxyfile.in
#        set(DOXY_DOC_EXCLUDE_PATTERNS_DIRS ${CMAKE_BINARY_DIR} CACHE STRING "Regex patterns exclusion")          ## used in the doxyfile.in
#        set(DOXY_DOC_COMMON_IMG_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Path from which doxygen will be able to found referenced images")## used in the doxyfile.in
#        configure_file(doxyfile.in ${CMAKE_BINARY_DIR}/doxyfile @ONLY)
#        add_custom_target(doxyDoc COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/doxyfile"
#            WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
#            COMMENT "Building user's documentation into doxyDoc build dir..."
#        )
#    endif()
#endif()
