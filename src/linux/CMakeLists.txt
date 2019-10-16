cmake_minimum_required(VERSION 3.8)

include(FindPkgConfig)
pkg_check_modules(SYSTEMD libsystemd REQUIRED)

set(SCLOG_LINUX_PLATFORM_SOURCES
    linux/sclog_systemd_sink.c
)

target_sources(${PROJECT_NAME}
	PRIVATE ${SCLOG_LINUX_PLATFORM_SOURCES}
)

set_property(TARGET ${PROJECT_NAME} APPEND
    PROPERTY PUBLIC_HEADER "linux/sclog_systemd_sink.h"
)

target_link_libraries(${PROJECT_NAME} ${SYSTEMD_LIBRARIES})
