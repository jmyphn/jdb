cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # export compile commands for clang-tidy
set(BUILD_SHARED_LIBS OFF) # static libraries; turn ON for shared libraries
set(CMAKE_CXX_STANDARD 20) # c++20 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(
    jdb
    VERSION 2025.5.25
    DESCRIPTION "Jimmy's Database (jdb)."
    LANGUAGES C CXX
)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message("No build type selected, defaulting to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message("project binaries: ${PROJECT_BINARY_DIR}")
message("project source: ${PROJECT_SOURCE_DIR}")

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" PATH_TO_CMAKELISTS_TXT)

if(EXISTS "${PATH_TO_CMAKELISTS_TXT}")
        message(FATAL_ERROR "Run CMake from a build subdirectory! \`mkdir build ; cd build ; cmake ..\` \
                Also, some junk files were created in this folder (CMakeCache.txt, CMakeFiles); you should delete those.")
endif()

message("Build mode: ${CMAKE_BUILD_TYPE}")

# debug compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-unused-parameter -Wno-attributes") # TODO: remove later
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb -fsanitize=${BUSTUB_SANITIZER} -fno-omit-frame-pointer -fno-optimize-sibling-calls")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Core
set(SOURCE_FILES src/common/db_instance.cpp)
add_library(jdb ${SOURCE_FILES})

# Shell
add_executable(jdb_shell src/shell.cpp)
target_link_libraries(jdb_shell jdb)

# Include
set(SRC_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/src/include
)
include_directories(${SRC_INCLUDE_DIR})