cmake_minimum_required(VERSION 3.8)
project(sclog_linux LANGUAGES C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SYSTEMD REQUIRED libsystemd)

if(SYSTEMD_FOUND AND SYSTEMD_LINK_LIBRARIES)
else()
endif()

add_library(SCLOG_LINUX OBJECT 
    "sclog_systemd_sink.c"
    "sclog_systemd_sink.h"
)

set_property(TARGET SCLOG_LINUX APPEND
    PROPERTY PUBLIC_HEADER "linux/sclog_systemd_sink.h"
)

target_link_libraries(SCLOG_LINUX INTERFACE ${SYSTEMD_LIBRARIES})

target_include_directories(SCLOG_LINUX PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/../
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../generated/>
    $<INSTALL_INTERFACE:include/sclog/linux>
)

install(TARGETS SCLOG_LINUX EXPORT SCLOG_LINUX
    PUBLIC_HEADER DESTINATION include/sclog/linux
)

set_target_properties(SCLOG_LINUX PROPERTIES
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
    C_VISIBILITY_PRESET hidden
)

