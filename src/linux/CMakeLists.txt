cmake_minimum_required(VERSION 3.8)
project(sclog_linux LANGUAGES C)

include(FindPkgConfig)
pkg_check_modules(SYSTEMD libsystemd REQUIRED)

add_library(SCLOG_LINUX OBJECT 
    sclog_systemd_sink.c
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

target_compile_features(SCLOG_LINUX PUBLIC $<$<NOT:$<C_COMPILER_ID:MSVC>>:c_std_11>)

set_target_properties(SCLOG_LINUX PROPERTIES
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
    C_VISIBILITY_PRESET hidden
)

