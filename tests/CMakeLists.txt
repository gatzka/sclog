cmake_minimum_required(VERSION 3.7)
project(sclog_unit_test C)
enable_testing()

add_library(fff INTERFACE)
target_include_directories(fff INTERFACE fff)

add_library(unity
    unity/src/unity.c
)
set_target_properties(unity PROPERTIES
    C_CLANG_TIDY ""
    COMPILE_OPTIONS "$<$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:Clang>>:-Wno-strict-overflow>"
    
)
target_include_directories(unity PUBLIC ${CMAKE_CURRENT_LIST_DIR}/unity/src/)

add_executable(test_sclog_version
    test_sclog_version.c
    ../src/sclog_version.c
)
add_test(NAME sclog.common.test_version COMMAND test_sclog_version)

get_property(includes TARGET sclog::sclog PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
get_property(targets DIRECTORY "${CMAKE_CURRENT_LIST_DIR}" PROPERTY BUILDSYSTEM_TARGETS)
foreach(tgt ${targets})
    get_target_property(target_type ${tgt} TYPE)
    if (target_type STREQUAL "EXECUTABLE")
        add_dependencies(${tgt} sclog::sclog) # Necessary to generage sclog_version_private.h before compiling the tests.
        target_link_libraries(${tgt} fff unity)
        target_include_directories(${tgt} PUBLIC ${includes})
        set_target_properties(${tgt} PROPERTIES
            C_STANDARD_REQUIRED ON
            C_EXTENSIONS OFF
            C_CLANG_TIDY ""
        )
    endif()
endforeach()


