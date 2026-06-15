project_add_e2e_test(gateway_service_e2e
    COMMAND
        ${CMAKE_CURRENT_SOURCE_DIR}/run_gateway_service_test.sh
    ARGUMENTS
        $<TARGET_FILE:gateway_service>
)
