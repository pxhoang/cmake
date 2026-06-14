# Small target helpers to keep bin/* and lib/* CMakeLists.txt files short.

function(project_add_interface_library target_name)
    add_library(${target_name} INTERFACE)
    add_library(project::${target_name} ALIAS ${target_name})

    target_include_directories(${target_name}
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    target_link_libraries(${target_name}
        INTERFACE
            project::options
            project::warnings
    )
endfunction()

function(project_add_library target_name)
    add_library(${target_name})
    add_library(project::${target_name} ALIAS ${target_name})

    target_include_directories(${target_name}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    target_link_libraries(${target_name}
        PUBLIC
            project::options

        PRIVATE
            project::warnings
    )
endfunction()

function(project_add_app_library target_name)
    add_library(${target_name})

    target_include_directories(${target_name}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}
    )

    target_link_libraries(${target_name}
        PUBLIC
            project::options

        PRIVATE
            project::warnings
    )
endfunction()

function(project_add_executable target_name)
    add_executable(${target_name})

    target_link_libraries(${target_name}
        PRIVATE
            project::options
            project::warnings
    )
endfunction()
