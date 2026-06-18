project_add_interface_library(gateway_device_services
    INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDENCIES
        project::gateway_device_ports
)
