# Typed test helpers keep unit, integration, and e2e workflows consistent.

include_guard(GLOBAL)
include(GoogleTest)

add_custom_target(project_unit_tests)
add_custom_target(project_integration_tests)

function(_project_add_gtest target_name test_type)
    cmake_parse_arguments(
        ARG
        ""
        "TIMEOUT"
        "SOURCES;DEPENDENCIES;LABELS"
        ${ARGN}
    )

    if(ARG_UNPARSED_ARGUMENTS)
        message(
            FATAL_ERROR
            "Unknown arguments for test '${target_name}': ${ARG_UNPARSED_ARGUMENTS}"
        )
    endif()

    if(NOT ARG_SOURCES)
        message(FATAL_ERROR "Test '${target_name}' requires SOURCES")
    endif()

    if(NOT ARG_TIMEOUT)
        if(test_type STREQUAL "unit")
            set(ARG_TIMEOUT 10)
        else()
            set(ARG_TIMEOUT 30)
        endif()
    endif()

    set(test_labels ${test_type} ${ARG_LABELS})

    project_add_executable(${target_name}
        SOURCES
            ${ARG_SOURCES}
        DEPENDENCIES
            GTest::gtest_main
            ${ARG_DEPENDENCIES}
    )

    gtest_discover_tests(${target_name}
        TEST_PREFIX "${test_type}."
        PROPERTIES
            LABELS "${test_labels}"
            TIMEOUT ${ARG_TIMEOUT}
        DISCOVERY_TIMEOUT 30
    )
endfunction()

function(project_add_unit_test target_name)
    _project_add_gtest(${target_name} unit ${ARGN})
    add_dependencies(project_unit_tests ${target_name})
endfunction()

function(project_add_integration_test target_name)
    _project_add_gtest(${target_name} integration ${ARGN})
    add_dependencies(project_integration_tests ${target_name})
endfunction()

function(project_add_e2e_test test_name)
    cmake_parse_arguments(
        ARG
        ""
        "COMMAND;WORKING_DIRECTORY;TIMEOUT"
        "ARGUMENTS;LABELS"
        ${ARGN}
    )

    if(ARG_UNPARSED_ARGUMENTS)
        message(
            FATAL_ERROR
            "Unknown arguments for test '${test_name}': ${ARG_UNPARSED_ARGUMENTS}"
        )
    endif()

    if(NOT ARG_COMMAND)
        message(FATAL_ERROR "E2E test '${test_name}' requires COMMAND")
    endif()

    if(NOT ARG_WORKING_DIRECTORY)
        set(ARG_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
    endif()

    if(NOT ARG_TIMEOUT)
        set(ARG_TIMEOUT 60)
    endif()

    add_test(
        NAME ${test_name}
        COMMAND ${ARG_COMMAND} ${ARG_ARGUMENTS}
    )

    set_tests_properties(${test_name}
        PROPERTIES
            LABELS "e2e;${ARG_LABELS}"
            TIMEOUT ${ARG_TIMEOUT}
            WORKING_DIRECTORY ${ARG_WORKING_DIRECTORY}
    )
endfunction()
