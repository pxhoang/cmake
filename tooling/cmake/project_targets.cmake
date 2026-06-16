# Declarative target helpers used by all project-owned components.

include_guard(GLOBAL)

function(_project_validate_target_arguments target_name)
    if(TARGET ${target_name})
        message(FATAL_ERROR "Target '${target_name}' already exists")
    endif()

    if(ARG_UNPARSED_ARGUMENTS)
        message(
            FATAL_ERROR
            "Unknown arguments for target '${target_name}': ${ARG_UNPARSED_ARGUMENTS}"
        )
    endif()
endfunction()

function(_project_enable_release_split_debug_symbols target_name)
    if(NOT PROJECT_RELEASE_SPLIT_DEBUG_SYMBOLS)
        return()
    endif()

    if(NOT CMAKE_OBJCOPY OR NOT CMAKE_STRIP)
        message(
            WARNING
            "PROJECT_RELEASE_SPLIT_DEBUG_SYMBOLS is enabled, but objcopy or strip was not found"
        )
        return()
    endif()

    if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
        return()
    endif()

    set(debug_file "$<TARGET_FILE:${target_name}>.debug")

    add_custom_command(
        TARGET ${target_name}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} --only-keep-debug "$<TARGET_FILE:${target_name}>" "${debug_file}"
        COMMAND ${CMAKE_STRIP} --strip-unneeded "$<TARGET_FILE:${target_name}>"
        COMMAND ${CMAKE_OBJCOPY} "--add-gnu-debuglink=${debug_file}" "$<TARGET_FILE:${target_name}>"
        VERBATIM
        COMMENT "Splitting debug symbols for ${target_name}"
    )

    set_property(
        TARGET ${target_name}
        APPEND
        PROPERTY ADDITIONAL_CLEAN_FILES "${debug_file}"
    )
endfunction()

function(project_add_interface_library target_name)
    cmake_parse_arguments(
        ARG
        ""
        ""
        "INCLUDE_DIRS;DEPENDENCIES"
        ${ARGN}
    )
    _project_validate_target_arguments(${target_name})

    if(NOT ARG_INCLUDE_DIRS)
        set(ARG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
    endif()

    add_library(${target_name} INTERFACE)
    add_library(project::${target_name} ALIAS ${target_name})

    target_include_directories(${target_name}
        INTERFACE
            ${ARG_INCLUDE_DIRS}
    )

    target_link_libraries(${target_name}
        INTERFACE
            project::options
            project::warnings
            ${ARG_DEPENDENCIES}
    )
endfunction()

function(project_add_library target_name)
    cmake_parse_arguments(
        ARG
        ""
        ""
        "SOURCES;PUBLIC_INCLUDE_DIRS;PRIVATE_INCLUDE_DIRS;PUBLIC_DEPENDENCIES;PRIVATE_DEPENDENCIES"
        ${ARGN}
    )
    _project_validate_target_arguments(${target_name})

    if(NOT ARG_SOURCES)
        message(FATAL_ERROR "Library '${target_name}' requires SOURCES")
    endif()

    if(NOT ARG_PUBLIC_INCLUDE_DIRS)
        set(ARG_PUBLIC_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
    endif()

    add_library(${target_name})
    add_library(project::${target_name} ALIAS ${target_name})

    target_sources(${target_name}
        PRIVATE
            ${ARG_SOURCES}
    )

    target_include_directories(${target_name}
        PUBLIC
            ${ARG_PUBLIC_INCLUDE_DIRS}
    )

    if(ARG_PRIVATE_INCLUDE_DIRS)
        target_include_directories(${target_name}
            PRIVATE
                ${ARG_PRIVATE_INCLUDE_DIRS}
        )
    endif()

    target_link_libraries(${target_name}
        PUBLIC
            project::options
            ${ARG_PUBLIC_DEPENDENCIES}

        PRIVATE
            project::warnings
            ${ARG_PRIVATE_DEPENDENCIES}
    )
endfunction()

function(project_add_executable target_name)
    cmake_parse_arguments(
        ARG
        "INSTALL"
        ""
        "SOURCES;DEPENDENCIES"
        ${ARGN}
    )
    _project_validate_target_arguments(${target_name})

    if(NOT ARG_SOURCES)
        message(FATAL_ERROR "Executable '${target_name}' requires SOURCES")
    endif()

    add_executable(${target_name})

    target_sources(${target_name}
        PRIVATE
            ${ARG_SOURCES}
    )

    target_link_libraries(${target_name}
        PRIVATE
            project::options
            project::warnings
            ${ARG_DEPENDENCIES}
    )

    if(ARG_INSTALL)
        _project_enable_release_split_debug_symbols(${target_name})

        install(
            TARGETS ${target_name}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        )

        if(PROJECT_RELEASE_SPLIT_DEBUG_SYMBOLS AND CMAKE_BUILD_TYPE STREQUAL "Release")
            install(
                FILES "$<TARGET_FILE:${target_name}>.debug"
                DESTINATION ${CMAKE_INSTALL_LIBDIR}/debug/${CMAKE_INSTALL_BINDIR}
            )
        endif()
    endif()
endfunction()
