project_add_test_executable(gateway_service_integration_tests)

target_sources(gateway_service_integration_tests
    PRIVATE
        file_channel_config_repository_test.cpp
)

target_link_libraries(gateway_service_integration_tests
    PRIVATE
        gateway_service_app
)
