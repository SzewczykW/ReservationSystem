############################################################################################################

cmake_minimum_required (VERSION 3.3.0 FATAL_ERROR)

# Set the output directory for the install executables and libraries
set (CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set (CMAKE_INSTALL_BINDIR ${CMAKE_INSTALL_PREFIX}/bin)
set (CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)

############################################################################################################

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

add_definitions (-DPROJECTPATH=\"${PROJECT_SOURCE_DIR}\")
add_definitions (-DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_definitions (-DPROJECT_BINARY_DIR=\"${PROJECT_BINARY_DIR}\")
add_definitions (-DCMAKE_BUILD_TYPE=\"${CMAKE_BUILD_TYPE}\")

############################################################################################################

# Create the project
project ("ReservationSystem" VERSION 0.0.1 LANGUAGES C CXX)

# C++ standard required by the project
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF) #No compiler specific extensions

# C compiler flags configuration checks
include (CheckCCompilerFlag)

# C++ compiler flags configuration checks
include (CheckCXXCompilerFlag)

# Set WARN_CXX_FLAGS
set (WARN_CXX_FLAGS "")

# Set the list of flags depending on the compiler
if (MSVC)
    set (WARN_CXX_FLAGS_TO_CHECK
        "/W4"                                                               # All warnings
        "/WX"                                                               # Treat warnings as errors                                                         
        )
else () # Assume GCC or Clang                               
    set (WARN_CXX_FLAGS_TO_CHECK                    
        "-Wall"                                                             # All warnings
        "-Wextra"                                                           # Extra warnings
        "-Wpedantic"                                                        # Pedantic warnings
        "-Werror"                                                           # Treat warnings as errors
        "-Wcast-align"                                                      # Warn for potential performance problem casts
        "-Wcast-qual"                                                       # Warn for casts discarding qualifiers
        )
endif ()

# Add build type flags to the list of flags to check
set (BUILD_TYPE_FLAGS "${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UPPER}}")
string (REPLACE " " ";" BUILD_TYPE_FLAGS_LIST ${BUILD_TYPE_FLAGS})
set (WARN_CXX_FLAGS_TO_CHECK_LIST "${WARN_CXX_FLAGS_TO_CHECK};${BUILD_TYPE_FLAGS_LIST}")

# Check if the compiler supports the flags
foreach (FLAG ${WARN_CXX_FLAGS_TO_CHECK_LIST})
    # Remove [+-=] signs from the flag
    string(REGEX REPLACE "[-=+]" "" FLAG_NO_SIGNS ${FLAG})
    # Check if the flag is supported by the compiler
    CHECK_CXX_COMPILER_FLAG (${FLAG} CXX_COMPILER_SUPPORTS_${FLAG_NO_SIGNS})
    # If so add it to the list of warning flags
    if (CXX_COMPILER_SUPPORTS_${FLAG_NO_SIGNS})
        set (WARN_CXX_FLAGS "${WARN_CXX_FLAGS} ${FLAG}")
    endif ()
endforeach ()

# Set CMAKE_CXX_FLAGS and CMAKE_C_FLAGS
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_CXX_FLAGS}")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WARN_CXX_FLAGS}")

if(CMAKE_CXX_COMPILER_LOADED AND CMAKE_C_COMPILER_LOADED)
    message (STATUS "C++ Compiler is loaded")
    message (STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
    message (STATUS "CMAKE_CXX_COMPILER_ID is ${CMAKE_CXX_COMPILER_ID}")
    message (STATUS "CMAKE_CXX_COMPILER is ${CMAKE_CXX_COMPILER}")
    message (STATUS "CMAKE_CXX_COMPILER_VERSION is ${CMAKE_CXX_COMPILER_VERSION}")
    message (STATUS "C Compiler is loaded")
    message (STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
    message (STATUS "CMAKE_C_COMPILER_ID is ${CMAKE_C_COMPILER_ID}")
    message (STATUS "CMAKE_C_COMPILER is ${CMAKE_C_COMPILER}")
    message (STATUS "CMAKE_C_COMPILER_VERSION is ${CMAKE_C_COMPILER_VERSION}")
elseif (CMAKE_CXX_COMPILER_LOADED)
    message (FATAL_ERROR "C Compiler is not loaded [FATAL ERROR]")
else ()
    message (FATAL_ERROR "C++ Compiler is not loaded [FATAL ERROR]")
endif ()

# Set include directories
set (INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories (${INCLUDES})

# Set source directories
file (GLOB SOURCES *.c *.cpp  *.h *.hpp */*.c */*.cpp */*.h */*.hpp)

# Generate shared library
add_library (${PROJECT_NAME}_library SHARED ${SOURCES})

target_include_directories (${PROJECT_NAME}_library PUBLIC ${INCLUDES})

############################################################################################################

# Generate executable
add_executable (${PROJECT_NAME} ${SOURCES})

# Link the executable to the shared library
target_link_libraries (${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_library)

# Binaries
install (TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR}) 

# Libraries
install (TARGETS ${PROJECT_NAME}_library
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

############################################################################################################

enable_testing ()

add_test (NAME Mem COMMAND valgrind --leak-check=full --track-origins=yes --error-exitcode=1 ./${PROJECT_NAME})

# test of program 

############################################################################################################

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