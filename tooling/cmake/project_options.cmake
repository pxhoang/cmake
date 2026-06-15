# Reusable build requirements for project-owned targets.

include_guard(GLOBAL)

option(PROJECT_WARNINGS_AS_ERRORS "Treat project warnings as errors" OFF)
option(PROJECT_ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)
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
