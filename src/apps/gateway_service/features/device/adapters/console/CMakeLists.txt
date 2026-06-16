project_add_library(gateway_device_console_adapter
    SOURCES
        console_device_controller.cpp
    PUBLIC_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC_DEPENDENCIES
        project::gateway_device_application
)
