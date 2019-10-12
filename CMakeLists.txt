cmake_minimum_required(VERSION 3.0)
project(sclog-all C)

#include(CTest)

add_subdirectory(src)
#add_subdirectory(tests)
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	add_subdirectory(examples)
endif()


set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)

include(ClangFormat)

file(GLOB FILES_TO_FORMAT
    ${PROJECT_SOURCE_DIR}/examples/*.c
    ${PROJECT_SOURCE_DIR}/examples/*.h
    ${PROJECT_SOURCE_DIR}/src/*.c
    ${PROJECT_SOURCE_DIR}/src/*.h
    ${PROJECT_SOURCE_DIR}/src/posix/*.c
    ${PROJECT_SOURCE_DIR}/src/posix/*.h
#   ${PROJECT_SOURCE_DIR}/tests/*.c
#   ${PROJECT_SOURCE_DIR}/tests/*.h
)

add_custom_target(sclog-format SOURCES ${FILES_TO_FORMAT})
AddClangFormat(sclog-format)
