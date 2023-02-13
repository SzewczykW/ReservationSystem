# Setup the project
cmake_minimum_required (VERSION 3.1.0)
project (reservation_system)

# global configuration
set(CMAKE_BUILD_TYPE Debug) 
message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_GCC_FLAGS "-O2")

# for static library
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# preventing in-source building
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed")
endif()

add_definitions(-DDATAPATH=\"${PROJECT_SOURCE_DIR}/data\")
add_compile_definitions("DEBUG=$<CONFIG:Debug>")

# Configure the components (subprojects)
# NOTE: The order matters! The most independent ones should go first.
#       If A and B really depend on each other, CMake  can build such correctly,
#       if you specify full path to the include directory
# add_subdirectory(lib)
# add_subdirectory(bin)