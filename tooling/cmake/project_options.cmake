# Reusable build requirements for project-owned targets.

include_guard(GLOBAL)

option(PROJECT_WARNINGS_AS_ERRORS "Treat project warnings as errors" OFF)
option(PROJECT_ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)
option(PROJECT_ENABLE_HARDENING "Enable conservative production hardening flags" OFF)
option(PROJECT_RELEASE_SPLIT_DEBUG_SYMBOLS "Generate separate debug symbols for Release binaries" OFF)
option(PROJECT_BUILD_INTEGRATION_TESTS "Build integration tests" ON)
option(PROJECT_BUILD_E2E_TESTS "Build end-to-end tests" ON)

add_library(project_options INTERFACE)
add_library(project::options ALIAS project_options)

target_compile_features(project_options
    INTERFACE
        cxx_std_20
)

add_library(project_warnings INTERFACE)
add_library(project::warnings ALIAS project_warnings)

target_compile_options(project_warnings
    INTERFACE
        $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang,AppleClang>:-Wall>
        $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang,AppleClang>:-Wextra>
        $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang,AppleClang>:-Wpedantic>
        $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/W4>
)

if(PROJECT_WARNINGS_AS_ERRORS)
    target_compile_options(project_warnings
        INTERFACE
            $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang,AppleClang>:-Werror>
            $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/WX>
    )
endif()

if(PROJECT_ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(project_options
        INTERFACE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
    )

    target_link_options(project_options
        INTERFACE
            -fsanitize=address,undefined
    )
endif()

if(PROJECT_RELEASE_SPLIT_DEBUG_SYMBOLS AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(project_options
        INTERFACE
            $<$<CONFIG:Release>:-g>
    )
endif()

if(PROJECT_ENABLE_HARDENING
        AND CMAKE_SYSTEM_NAME STREQUAL "Linux"
        AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_definitions(project_options
        INTERFACE
            $<$<CONFIG:Release>:_FORTIFY_SOURCE=2>
    )

    target_compile_options(project_options
        INTERFACE
            $<$<CONFIG:Release>:-fstack-protector-strong>
            $<$<CONFIG:Release>:-fPIE>
    )

    target_link_options(project_options
        INTERFACE
            $<$<CONFIG:Release>:-pie>
            $<$<CONFIG:Release>:-Wl,-z,relro>
            $<$<CONFIG:Release>:-Wl,-z,now>
    )
endif()
