project_add_app_library(gateway_service_app)

target_sources(gateway_service_app
    PRIVATE
        bootstrap/bootstrap.cpp

        infrastructure/config/app_config.cpp

        features/channel/api/channel_api.cpp

        features/channel/persistence/file_channel_config_repository.cpp
        features/channel/persistence/fake_radio_device.cpp
)

target_link_libraries(gateway_service_app
    PUBLIC
        project::common
        project::protocol
)

project_add_executable(gateway_service)

target_sources(gateway_service
    PRIVATE
        main.cpp
)

target_link_libraries(gateway_service
    PRIVATE
        gateway_service_app
)

project_add_test_executable(gateway_service_channel_domain_test)

target_sources(gateway_service_channel_domain_test
    PRIVATE
        tests/unit/channel_domain_test.cpp
)

target_link_libraries(gateway_service_channel_domain_test
    PRIVATE
        gateway_service_app
)

project_add_test_executable(gateway_service_set_channel_use_case_test)

target_sources(gateway_service_set_channel_use_case_test
    PRIVATE
        tests/unit/set_channel_use_case_test.cpp
)

target_link_libraries(gateway_service_set_channel_use_case_test
    PRIVATE
        gateway_service_app
)

project_add_test_executable(gateway_service_channel_api_test)

target_sources(gateway_service_channel_api_test
    PRIVATE
        tests/unit/channel_api_test.cpp
)

target_link_libraries(gateway_service_channel_api_test
    PRIVATE
        gateway_service_app
)
