cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build: None, Debug, Release"
        FORCE)
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# prevent in-source builds
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "In-source builds are not allowed.")
endif ()

# Create the project
project("ReservationSystem" C)

# C standard required by the project
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF) #No compiler specific extensions

# Compiler flags depending on the compiler
if(MSVC)
    set(C_FLAGS
    "/W4" # most warnings
    )
else()
    set(C_FLAGS
        "-Wpointer-arith"               # Warn about anything that depends on the sizeof(pointer)
        "-Wno-write-strings"            # Don't warn about writing to string literals
        "-Wall"                         # Most warnings
        "-Wextra"                       # Extra warnings
        "-Wpedantic"                    # Ensure ISO compliance (i.e. no non-standard extensions)
        "-Wcast-qual"                   # Warn if cast removes qualifier
        "-Wcast-align"                  # Warn if a cast causes memory alignment changes
        "-Wshadow"                      # Warn if local variable shadows another variable
        "-Wno-format-nonliteral"        # Don't warn about non-literal format strings
        "-Wlogical-op"                  # Checks for logical op when bit-wise expected
        "-Wmissing-declarations"        # Warn if a global function is defined with no declaration
        "-Wmissing-include-dirs"        # Warn if a user include directory is missing
        "-Wredundant-decls"             # Warn if there are overlapping declarations
        "-Wswitch-default"              # Warn if a switch has no default
        "-Wunused"                      # Warn about unused variables/parameters
        "-Wunused-variable"             # Warn about variables that are not used
        "-Wunused-parameter"            # Warn about function parameters which are unused
        "-Wdisabled-optimization"       # Warn when optimizations are skipped
        "-Wduplicated-cond"             # Warn about identical conditions in if-else chains
        "-Wduplicated-branches"         # Warn when different branches of an if-else chain are equivalent
        "-Wnull-dereference"            # Warn about null pointer dereference execution paths
        "-Wuninitialized"               # Warn about unitialized values
        "-Winit-self"                   # Warn about self-initialization
        "-Wextra-semi"                  # Warn about extra semicolons
        "-std=c17"                      # C standard
        )
endif()

# Set include directories
set(INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDES})

# Set source directories
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

# Generate shared library
add_library(${PROJECT_NAME}_library SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME}_library PUBLIC ${INCLUDES})

# Generate executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link the executable to the shared library
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_library)

# Binaries
install (TARGETS ${PROJECT_NAME} DESTINATION bin)

enable_testing()

add_test(NAME Mem COMMAND valgrind --leak-check=full --track-origins=yes --error-exitcode=1 ./${PROJECT_NAME}_binary)


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