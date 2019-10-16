cmake_minimum_required(VERSION 3.8)

include(FindPkgConfig)
pkg_check_modules(SYSTEMD libsystemd REQUIRED)

add_library(LINUX_OBJECTS OBJECT 
    linux/sclog_systemd_sink.c
)

target_link_libraries(${PROJECT_NAME} INTERFACE ${SYSTEMD_LIBRARIES})

set_property(TARGET LINUX_OBJECTS APPEND
    PROPERTY PUBLIC_HEADER "linux/sclog_systemd_sink.h"
)

target_include_directories(LINUX_OBJECTS PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/../
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated/>
    $<INSTALL_INTERFACE:include/sclog/linux>
)

install(TARGETS LINUX_OBJECTS EXPORT LINUX_OBJECTS
    PUBLIC_HEADER DESTINATION include/sclog/linux
)

target_compile_features(LINUX_OBJECTS PUBLIC $<$<NOT:$<C_COMPILER_ID:MSVC>>:c_std_11>)

set_target_properties(LINUX_OBJECTS PROPERTIES
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
    C_VISIBILITY_PRESET hidden
)

