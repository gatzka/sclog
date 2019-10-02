cmake_minimum_required(VERSION 3.7)
project(sclog-examples C)

add_executable(log_stderr
    log_stderr.c
)
target_link_libraries (log_stderr)

get_property(targets DIRECTORY "${CMAKE_CURRENT_LIST_DIR}" PROPERTY BUILDSYSTEM_TARGETS)
foreach(tgt ${targets})
    get_target_property(target_type ${tgt} TYPE)
    if (target_type STREQUAL "EXECUTABLE")
        target_link_libraries(${tgt} sclog:sclog)
        set_target_properties(${tgt} PROPERTIES
    		C_STANDARD_REQUIRED ON
    		C_EXTENSIONS OFF
            C_CLANG_TIDY ""
        )
    endif()
endforeach()
