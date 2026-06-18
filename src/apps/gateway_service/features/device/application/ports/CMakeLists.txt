project_add_interface_library(gateway_device_ports
    INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDENCIES
        project::gateway_device_domain
)
