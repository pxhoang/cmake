if(PROJECT_BUILD_INTEGRATION_TESTS)
    add_subdirectory(integration)
endif()

if(PROJECT_BUILD_E2E_TESTS)
    add_subdirectory(e2e)
endif()
