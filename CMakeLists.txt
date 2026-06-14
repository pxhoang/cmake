cmake_minimum_required(VERSION 3.24)

project(sample_project LANGUAGES CXX)

option(PROJECT_ENABLE_EXTERNALS "Download/build external dependencies" OFF)

enable_testing()

include(cmake/project_options.cmake)
include(cmake/project_targets.cmake)
include(external/googletest/external.cmake)
include(cmake/project_tests.cmake)

if(PROJECT_ENABLE_EXTERNALS)
    include(external/spdlog/external.cmake)
endif()

add_subdirectory(lib)
add_subdirectory(bin)
add_subdirectory(tests)
