add_subdirectory(features/device)
add_subdirectory(infrastructure/config)
add_subdirectory(bootstrap)

project_add_executable(gateway_service
    INSTALL
    SOURCES
        main.cpp
    DEPENDENCIES
        project::gateway_composition
        Threads::Threads
)

install(
    FILES ${CMAKE_SOURCE_DIR}/ops/deploy/systemd/gateway_service.service
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/systemd/system
)

install(
    FILES ${CMAKE_SOURCE_DIR}/ops/config/gateway_service/example.env
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/doc/gateway-service
)

if(BUILD_TESTING)
    add_subdirectory(tests/unit)
endif()
