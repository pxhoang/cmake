project_add_unit_test(gateway_service_device_domain_test
    SOURCES
        device_domain_test.cpp
    DEPENDENCIES
        project::gateway_device_domain
)

project_add_unit_test(gateway_service_select_device_use_case_test
    SOURCES
        select_device_use_case_test.cpp
    DEPENDENCIES
        project::gateway_device_application
)

project_add_unit_test(gateway_service_reconcile_device_use_case_test
    SOURCES
        reconcile_device_use_case_test.cpp
    DEPENDENCIES
        project::gateway_device_application
)

project_add_unit_test(gateway_service_device_api_test
    SOURCES
        device_api_test.cpp
    DEPENDENCIES
        project::gateway_device_api
)

project_add_unit_test(gateway_service_app_config_test
    SOURCES
        app_config_test.cpp
    DEPENDENCIES
        project::gateway_config
)
