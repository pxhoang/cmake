# Test helpers for unit, integration, and e2e targets.

include(GoogleTest)

function(project_add_test_executable target_name)
    add_executable(${target_name})

    target_link_libraries(${target_name}
        PRIVATE
            GTest::gtest_main
            project::options
            project::warnings
    )

    gtest_discover_tests(${target_name})
endfunction()

function(project_add_shell_test test_name script_path)
    add_test(
        NAME ${test_name}
        COMMAND ${script_path}
    )

    set_tests_properties(${test_name}
        PROPERTIES
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endfunction()
