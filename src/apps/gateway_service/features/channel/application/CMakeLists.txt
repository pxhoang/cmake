project_add_interface_library(gateway_channel_application
    INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDENCIES
        project::gateway_channel_domain
)
