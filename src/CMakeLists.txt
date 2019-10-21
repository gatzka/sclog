cmake_minimum_required(VERSION 3.8)
project(sclog VERSION 0.0.1 LANGUAGES C)

find_package(Git QUIET REQUIRED)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/../.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

include(CMakePackageConfigHelpers)

add_custom_target(generate_semver
    COMMAND ${CMAKE_COMMAND}
        -DPROJECT_NAME=${PROJECT_NAME}
        -DPROJECT_VERSION_MAJOR=${${PROJECT_NAME}_VERSION_MAJOR}
        -DPROJECT_VERSION_MINOR=${${PROJECT_NAME}_VERSION_MINOR}
        -DPROJECT_VERSION_PATCH=${${PROJECT_NAME}_VERSION_PATCH}
        -DGIT_WORK_DIR=${CMAKE_CURRENT_LIST_DIR}
        -DINPUT_FILE=${CMAKE_CURRENT_LIST_DIR}/sclog_version_private.h.in
        -DOUTPUT_FILE=${CMAKE_CURRENT_BINARY_DIR}/generated/sclog_version_private.h
        -P ${CMAKE_CURRENT_SOURCE_DIR}/generate_version.cmake
)

include(CMakeDependentOption)

SET(IS_POSIX OFF)
SET(IS_LINUX OFF)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    SET(IS_POSIX ON)
    SET(IS_LINUX ON)
endif()

cmake_dependent_option(SCLOG_CONFIG_POSIX "Add POSIX conformant logging support to the library" ON "IS_POSIX" OFF)
cmake_dependent_option(SCLOG_CONFIG_LINUX "Add Linux dependent support to the library" ON "IS_LINUX" OFF)

add_library(${PROJECT_NAME}
    "sclog.c"
    "sclog_file_rotate_sink.c"
    "sclog_file_write.c"
    "sclog_null_sink.c"
    "sclog_stderr_sink.c"
    "sclog_version.c"
)
if(IS_POSIX)
    target_sources(${PROJECT_NAME} PRIVATE $<TARGET_OBJECTS:POSIX_OBJECTS>)
endif()
if(IS_LINUX)
    target_sources(${PROJECT_NAME} PRIVATE $<TARGET_OBJECTS:LINUX_OBJECTS>)
endif()

if(${SCLOG_CONFIG_POSIX})
    include(posix/CMakeLists.txt)
endif()

if(${SCLOG_CONFIG_LINUX})
    include(linux/CMakeLists.txt)
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    include(platform/linux/CMakeLists.txt)
    target_sources(${PROJECT_NAME} PRIVATE $<TARGET_OBJECTS:LINUX_PLATFORM_OBJECTS>)
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    include(platform/windows/CMakeLists.txt)
    target_sources(${PROJECT_NAME} PRIVATE $<TARGET_OBJECTS:WINDOWS_PLATFORM_OBJECTS>)
endif()

add_library(${PROJECT_NAME}:${PROJECT_NAME} ALIAS ${PROJECT_NAME})

add_dependencies(${PROJECT_NAME} generate_semver)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated/>
    $<INSTALL_INTERFACE:include/sclog/>
)

target_compile_features(${PROJECT_NAME} PUBLIC $<$<NOT:$<C_COMPILER_ID:MSVC>>:c_std_11>)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
    SOVERSION ${PROJECT_VERSION_MAJOR}
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
    C_VISIBILITY_PRESET hidden
)

set_property(TARGET ${PROJECT_NAME}
    APPEND
    PROPERTY PUBLIC_HEADER "sclog.h;sclog_version.h;sclog_file_rotate.h;sclog_compiler.h;sclog_null_sink.h;sclog_stderr_sink.h"
)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/generated/${PROJECT_NAME}_export.h)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/sclog
)

write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${${PROJECT_NAME}_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION lib/cmake/${PROJECT_NAME}
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/generated/${PROJECT_NAME}_export.h"
    DESTINATION include/sclog/
)

install(EXPORT ${PROJECT_NAME}
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake/${PROJECT_NAME}
    FILE ${PROJECT_NAME}Config.cmake
)

include(FindDoxygen)

if (DOXYGEN_FOUND)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_EXTRACT_STATIC YES)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_HAVE_DOT NO)
    set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
    set(DOXYGEN_OUTPUT_DIRECTORY docs/)
	set(DOXYGEN_PROJECT_BRIEF "An ANSI C Conformant Log Library.")
	set(DOXYGEN_PROJECT_NUMBER ${${PROJECT_NAME}_VERSION})
    set(DOXYGEN_QUIET YES)
    set(DOXYGEN_RECURSIVE NO)
    set(DOXYGEN_STRICT_PROTO_MATCHING YES)
    set(DOXYGEN_STRIP_FROM_PATH ${CMAKE_CURRENT_BINARY_DIR}/generated/ ${CMAKE_CURRENT_SOURCE_DIR})
    set(DOXYGEN_WARN_AS_ERROR YES)
    set(DOXYGEN_PROJECT_NAME ${CMAKE_PROJECT_NAME})
    set(DOXYGEN_EXCLUDE_PATTERNS "*private*;*.c")

    doxygen_add_docs(docs
        ${PROJECT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/generated/
        COMMENT "Generating API documentation with Doxygen"
    )
else (DOXYGEN_FOUND)
    message(STATUS "Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
