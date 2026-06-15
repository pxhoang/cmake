project_add_library(gateway_channel_radio_adapter
    SOURCES
        console_radio_device.cpp
    PUBLIC_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC_DEPENDENCIES
        project::gateway_channel_application
)
