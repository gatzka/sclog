cmake_minimum_required(VERSION 3.8)

add_library(WINDOWS_PLATFORM_OBJECTS OBJECT 
    platform/windows/sclog_windows_time.c
)

target_include_directories(WINDOWS_PLATFORM_OBJECTS PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/../../
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated/>
)

set_target_properties(WINDOWS_PLATFORM_OBJECTS PROPERTIES
    C_VISIBILITY_PRESET hidden
)

