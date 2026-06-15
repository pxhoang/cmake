project_add_unit_test(gateway_service_channel_domain_test
    SOURCES
        channel_domain_test.cpp
    DEPENDENCIES
        project::gateway_channel_domain
)

project_add_unit_test(gateway_service_set_channel_use_case_test
    SOURCES
        set_channel_use_case_test.cpp
    DEPENDENCIES
        project::gateway_channel_application
)

project_add_unit_test(gateway_service_reconcile_channel_use_case_test
    SOURCES
        reconcile_channel_use_case_test.cpp
    DEPENDENCIES
        project::gateway_channel_application
)

project_add_unit_test(gateway_service_channel_api_test
    SOURCES
        channel_api_test.cpp
    DEPENDENCIES
        project::gateway_channel_api
)

project_add_unit_test(gateway_service_app_config_test
    SOURCES
        app_config_test.cpp
    DEPENDENCIES
        project::gateway_config
)
