cmake_minimum_required(VERSION 3.8)

add_library(SCLOG_POSIX OBJECT 
    "sclog_posix_util.c"
    "sclog_posix_util.h"
    "sclog_syslog_sink.c"
    "sclog_syslog_sink.h"
)

set_property(TARGET SCLOG_POSIX APPEND
    PROPERTY PUBLIC_HEADER "posix/sclog_syslog_sink.h"
)

target_include_directories(SCLOG_POSIX PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/../
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../generated/>
    $<INSTALL_INTERFACE:include/sclog/posix>
)

install(TARGETS SCLOG_POSIX EXPORT SCLOG_POSIX
    PUBLIC_HEADER DESTINATION include/sclog/posix
)

target_compile_features(SCLOG_POSIX PUBLIC $<$<NOT:$<C_COMPILER_ID:MSVC>>:c_std_11>)

set_target_properties(SCLOG_POSIX PROPERTIES
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
    C_VISIBILITY_PRESET hidden
)

