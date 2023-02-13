cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(Reservation_system)

# set(CMAKE_C_STANDARD 17 CACHE STRING "C standard to conform to" FORCE)
# set(CMAKE_C_STANDARD 17 CACHE STRING "C standard to conform to" FORCE)
# set(CMAKE_C_STANDARD_REQUIRED ON CACHE BOOL "C standard is required" FORCE)
# set(CMAKE_C_EXTENSIONS OFF CACHE BOOL "C extensions are not used" FORCE)

# prevent in-source builds
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON CACHE BOOL "Disable in source build" FORCE)
set(CMAKE_DISABLE_SOURCE_CHANGES ON CACHE BOOL "Disable source changes" FORCE)
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

add_definitions(-DPROJECTPATH=\"${PROJECT_SOURCE_DIR}\")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDES})

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS}-O2")
set(CMAKE_C_STANDARD_REQUIRED ON)

if(INCLUDES_TEST)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DLIB_TEST")
endif()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -O2")

add_executable(${PROJECT_NAME} ${SOURCES})

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