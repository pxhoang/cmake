project_add_library(protocol)

target_sources(protocol
    PRIVATE
        src/text_format.cpp
)

target_link_libraries(protocol
    PUBLIC
        project::common
)

project_add_test_executable(protocol_unit_tests)

target_sources(protocol_unit_tests
    PRIVATE
        tests/text_format_test.cpp
)

target_link_libraries(protocol_unit_tests
    PRIVATE
        project::protocol
)
