project_add_library(protocol
    SOURCES
        src/text_format.cpp
)

if(BUILD_TESTING)
    project_add_unit_test(protocol_unit_tests
        SOURCES
            tests/text_format_test.cpp
        DEPENDENCIES
            project::protocol
    )
endif()
