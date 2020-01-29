cmake_minimum_required(VERSION 3.7)
project(sclog-examples C)

set(IS_LINUX OFF)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(IS_LINUX ON)
endif()

add_executable(stderr_log_example
    stderr_log_example.c
)
target_link_libraries (stderr_log_example)


if(IS_LINUX)
    find_library(SYSD_LIB systemd)
    if(SYSD_LIB)
        add_executable(systemd_log_example
            systemd_log_example.c
        )
        target_link_libraries (systemd_log_example)
    endif()

    add_executable(syslog_log_example
        syslog_log_example.c
    )
    target_link_libraries (syslog_log_example)
endif()

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
