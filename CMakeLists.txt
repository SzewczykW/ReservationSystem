cmake_minimum_required (VERSION 3.1.0)

project (reservation_system)

# preventin in-source builds
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are not allowed.")
endif()

