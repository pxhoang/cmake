include(ExternalProject)

set(SPDLOG_SOURCE_DIR
    ${CMAKE_SOURCE_DIR}/.img/external/src/spdlog
)

set(SPDLOG_BUILD_DIR
    ${CMAKE_SOURCE_DIR}/.img/external/build/spdlog
)

set(SPDLOG_INSTALL_DIR
    ${CMAKE_SOURCE_DIR}/.img/external/install/spdlog
)

# This recipe is intentionally disabled by default through PROJECT_ENABLE_EXTERNALS=OFF.
# Replace the placeholder hash before enabling it.
ExternalProject_Add(spdlog_external
    URL
        https://github.com/gabime/spdlog/archive/refs/tags/v1.14.1.tar.gz

    URL_HASH
        SHA256=<put-real-sha256-here>

    SOURCE_DIR
        ${SPDLOG_SOURCE_DIR}

    BINARY_DIR
        ${SPDLOG_BUILD_DIR}

    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${SPDLOG_INSTALL_DIR}
        -DSPDLOG_BUILD_TESTS=OFF
        -DSPDLOG_BUILD_EXAMPLE=OFF
        -DSPDLOG_BUILD_SHARED=OFF

    BUILD_BYPRODUCTS
        ${SPDLOG_INSTALL_DIR}/lib/libspdlog.a
)

add_library(external_spdlog STATIC IMPORTED GLOBAL)

add_dependencies(external_spdlog spdlog_external)

set_target_properties(external_spdlog
    PROPERTIES
        IMPORTED_LOCATION
            ${SPDLOG_INSTALL_DIR}/lib/libspdlog.a

        INTERFACE_INCLUDE_DIRECTORIES
            ${SPDLOG_INSTALL_DIR}/include
)

add_library(external::spdlog ALIAS external_spdlog)
