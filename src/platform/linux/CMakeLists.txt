cmake_minimum_required(VERSION 3.8)

add_library(LINUX_PLATFORM_OBJECTS OBJECT 
    platform/linux/sclog_linux_time.c
)

target_include_directories(LINUX_PLATFORM_OBJECTS PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/../../
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated/>
)

set_target_properties(LINUX_PLATFORM_OBJECTS PROPERTIES
    C_VISIBILITY_PRESET hidden
)

