project_add_library(gateway_config
    SOURCES
        app_config.cpp
    PUBLIC_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC_DEPENDENCIES
        project::gateway_device_domain
)
