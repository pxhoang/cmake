project_add_library(gateway_channel_file_adapter
    SOURCES
        file_channel_config_repository.cpp
    PUBLIC_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC_DEPENDENCIES
        project::gateway_channel_application
)
