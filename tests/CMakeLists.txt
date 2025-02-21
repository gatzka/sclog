cmake_minimum_required(VERSION 3.11)
project(sclog_unit_test C)

find_package(Git QUIET REQUIRED)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/../.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

enable_testing()

add_library(fff_sclog INTERFACE)
target_include_directories(fff_sclog INTERFACE fff)

add_library(unity_sclog
    unity/src/unity.c
)
set_target_properties(unity_sclog PROPERTIES
    C_CLANG_TIDY ""
    COMPILE_OPTIONS "$<$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:Clang>>:-Wno-strict-overflow>"
    
)
target_include_directories(unity_sclog PUBLIC ${CMAKE_CURRENT_LIST_DIR}/unity/src/)

add_executable(test_sclog_version
    test_sclog_version.c
    ../lib/src/version.c
)
add_test(NAME sclog.common.test_version COMMAND test_sclog_version)

get_property(includes TARGET sclog::sclog PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
get_property(targets DIRECTORY "${CMAKE_CURRENT_LIST_DIR}" PROPERTY BUILDSYSTEM_TARGETS)
foreach(tgt ${targets})
    get_target_property(target_type ${tgt} TYPE)
    if (target_type STREQUAL "EXECUTABLE")
        add_dependencies(${tgt} sclog::sclog) # Necessary to generage sclog_version_private.h before compiling the tests.
        target_link_libraries(${tgt} fff_sclog unity_sclog)
        target_include_directories(${tgt} PUBLIC ${includes})
        set_target_properties(${tgt} PROPERTIES
            C_STANDARD_REQUIRED ON
            C_EXTENSIONS OFF
            C_CLANG_TIDY ""
        )
    endif()
endforeach()


