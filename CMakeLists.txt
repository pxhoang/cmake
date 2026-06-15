cmake_minimum_required(VERSION 3.24)

project(sample_project VERSION 1.0.0 LANGUAGES CXX)

include(CTest)
include(GNUInstallDirs)
find_package(Threads REQUIRED)

include(tooling/cmake/project_options.cmake)
include(tooling/cmake/project_targets.cmake)

if(BUILD_TESTING)
    include(tooling/cmake/dependencies/googletest.cmake)
    include(tooling/cmake/project_tests.cmake)
endif()

add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

set(CPACK_PACKAGE_NAME gateway-service)
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR TGZ)
set(CPACK_PACKAGING_INSTALL_PREFIX /usr)
include(CPack)
