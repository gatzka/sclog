cmake_minimum_required(VERSION 3.8)

add_library(POSIX_OBJECTS OBJECT 
    posix/sclog_syslog_sink.c
    posix/sclog_posix_util.c
)

set_property(TARGET POSIX_OBJECTS APPEND
    PROPERTY PUBLIC_HEADER "posix/sclog_syslog_sink.h"
)

target_include_directories(POSIX_OBJECTS PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/../
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated/>
    $<INSTALL_INTERFACE:include/sclog/posix>
)

install(TARGETS POSIX_OBJECTS EXPORT POSIX_OBJECTS
    PUBLIC_HEADER DESTINATION include/sclog/posix
)

target_compile_features(POSIX_OBJECTS PUBLIC $<$<NOT:$<C_COMPILER_ID:MSVC>>:c_std_11>)

set_target_properties(POSIX_OBJECTS PROPERTIES
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
    C_VISIBILITY_PRESET hidden
)

