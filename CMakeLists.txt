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
            
