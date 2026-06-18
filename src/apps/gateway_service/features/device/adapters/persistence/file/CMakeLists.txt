project_add_library(gateway_device_file_persistence
    SOURCES
        file_device_state_repository.cpp
    PUBLIC_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC_DEPENDENCIES
        project::gateway_device_ports
)
