############################################################################################################

cmake_minimum_required ( VERSION 3.3.0 FATAL_ERROR )
project ( "Doxygen documentation" )

############################################################################################################

option (BUILD_DOXY_DOC "build doxygen documentation" ON)
if (BUILD_DOXY_DOC)
    find_package (Doxygen REQUIRED dot)
    if (NOT DOXYGEN_FOUND)
        message (WARNING "Doxygen not found, unable to generate documentation")
    else ()
        set (DOXY_DOC_DEST_DIR ${CMAKE_BINARY_DIR} CACHE PATH "Path to the doxygen output")                      ## used in the doxyfile.in
        set (DOXY_DOC_INPUT_ROOT_DIRS ${CMAKE_HOME_DIRECTORY} CACHE PATH "Path from where to start to parse")    ## used in the doxyfile.in
        set (DOXY_DOC_EXCLUDE_PATTERNS_DIRS ${CMAKE_BINARY_DIR} CACHE STRING "Regex patterns exclusion")          ## used in the doxyfile.in
        set (DOXY_DOC_COMMON_IMG_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Path from which doxygen will be able to found referenced images")## used in the doxyfile.in
        configure_file (doxyfile.in ${CMAKE_BINARY_DIR}/doxyfile @ONLY)
        add_custom_target (doxyDoc COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/doxyfile"
            WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
            COMMENT "Building user's documentation into doxyDoc build dir..."
        )
    endif ()
endif ()

############################################################################################################