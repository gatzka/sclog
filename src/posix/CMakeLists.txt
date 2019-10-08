cmake_minimum_required(VERSION 3.8)

set(SCLOG_POSIX_PLATFORM_SOURCES
    posix/sclog_syslog_sink.c
)

target_sources(${PROJECT_NAME}
    PRIVATE ${SCLOG_POSIX_PLATFORM_SOURCES}
)

set_property(TARGET ${PROJECT_NAME} APPEND
    PROPERTY PUBLIC_HEADER "posix/sclog_stderr_sink.h"
)

