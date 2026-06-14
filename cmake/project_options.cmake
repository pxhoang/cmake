# Reusable build requirements for project-owned targets.

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


# add_executable()
# add_library(project_executable_options INTERFACE)
# add_library(project_executable_options INTERFACE)

# target_compile_definitions()
# target_compile_features()
# target_compile_options()
# target_include_directories()
# target_link_directories()
# target_link_libraries()
# target_link_options()
# target_precompile_headers()
# target_sources()

# ------------------------------------------------------------------------------
# 
# ------------------------------------------------------------------------------

# add_compile_definitions()
# add_compile_options()
# add_custom_command()
# add_custom_target()
# add_definitions()
# add_dependencies()
# add_executable()
# add_library()
# add_subdirectory()
# add_test()

# add_subdirectory()
# add_library()
# add_executable()

# target_com


# create target
# add_executable(myapp)
# add_library(mylib)

# add build requirements to target