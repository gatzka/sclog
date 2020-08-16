cmake_minimum_required(VERSION 3.8)
project(sclog VERSION 0.0.1 LANGUAGES C)

add_custom_target(${PROJECT_NAME}_generate_semver
    COMMAND ${CMAKE_COMMAND}
        -DPROJECT_NAME=${PROJECT_NAME}
        -DPROJECT_VERSION_MAJOR=${${PROJECT_NAME}_VERSION_MAJOR}
        -DPROJECT_VERSION_MINOR=${${PROJECT_NAME}_VERSION_MINOR}
        -DPROJECT_VERSION_PATCH=${${PROJECT_NAME}_VERSION_PATCH}
        -DGIT_WORK_DIR=${CMAKE_CURRENT_LIST_DIR}
        -DINPUT_FILE=${CMAKE_CURRENT_LIST_DIR}/include/sclog/version_private.h.in
        -DOUTPUT_FILE=${CMAKE_CURRENT_BINARY_DIR}/generated/sclog/version_private.h
        -P ${CMAKE_CURRENT_SOURCE_DIR}/generate_version.cmake
)

add_library(${PROJECT_NAME}
    include/sclog/compiler.h
    include/sclog/file_rotate.h
    include/sclog/file_write.h
    include/sclog/null_sink.h
    include/sclog/sclog.h
    include/sclog/stderr_sink.h
    include/sclog/time.h
    include/sclog/util.h
    include/sclog/version.h
    src/file_rotate_sink.c
    src/file_write.c
    src/null_sink.c
    src/sclog.c
    src/stderr_sink.c
    src/version.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated/>
)

set(IS_LINUX OFF)
set(IS_WINDOWS OFF)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(IS_LINUX ON)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(IS_WINDOWS ON)
endif()

if(IS_LINUX)
    target_sources(${PROJECT_NAME} PRIVATE
        src/platform/linux/time.c
    )

    find_library(SYSD_LIB systemd)
    if(SYSD_LIB)
        option(SCLOG_CONFIG_SYSTEMD "Add support for systemd log facility" ON)
    endif()

    option(SCLOG_CONFIG_SYSLOG "Add support for syslog log facility" ON)

    if(SCLOG_CONFIG_SYSLOG)
        target_sources(${PROJECT_NAME} PRIVATE
            src/platform/posix/syslog_sink.c
            src/platform/posix/util.c
        )
        
        target_include_directories(${PROJECT_NAME} PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/platform/posix/>
        )
        set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY PUBLIC_HEADER
            include/platform/posix/sclog/posix_util.h
            include/platform/posix/sclog/syslog_sink.h
        )
    endif()

    if(SCLOG_CONFIG_SYSTEMD)
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(SYSTEMD REQUIRED libsystemd)

        target_sources(${PROJECT_NAME} PRIVATE
            src/platform/linux/systemd_sink.c
        )

        target_include_directories(${PROJECT_NAME} PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/platform/linux/>
        )

        target_link_libraries(${PROJECT_NAME} INTERFACE ${SYSTEMD_LIBRARIES})

        set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY PUBLIC_HEADER
            include/platform/linux/sclog/systemd_sink.h
        )
    endif()
elseif(IS_WINDOWS)
    target_sources(${PROJECT_NAME} PRIVATE
        src/platform/windows/time.c
    )
endif()

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_generate_semver)


target_compile_features(${PROJECT_NAME} PUBLIC $<$<NOT:$<C_COMPILER_ID:MSVC>>:c_std_11>)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
    SOVERSION ${PROJECT_VERSION_MAJOR}
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
    C_VISIBILITY_PRESET hidden
)

set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY PUBLIC_HEADER
    include/sclog/compiler.h
    include/sclog/file_rotate.h
    include/sclog/null_sink.h
    include/sclog/sclog.h
    include/sclog/stderr_sink.h
    include/sclog/version.h
)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/generated/${PROJECT_NAME}/export.h)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME} ${INSTALL_TARGET_LIST}
    EXPORT ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${${PROJECT_NAME}_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION lib/cmake/${PROJECT_NAME}
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/generated/${PROJECT_NAME}/export.h"
    DESTINATION include/sclog/
)

install(EXPORT ${PROJECT_NAME}
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake/${PROJECT_NAME}
    FILE ${PROJECT_NAME}Config.cmake
)

include(FindDoxygen)

if(DOXYGEN_FOUND)
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
    set(DOXYGEN_STRIP_FROM_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sclog/
        ${CMAKE_CURRENT_SOURCE_DIR}/include/platform/posix/sclog/
        ${CMAKE_CURRENT_SOURCE_DIR}/include/platform/linux/sclog/
        ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/
    )
    set(DOXYGEN_WARN_AS_ERROR YES)
    set(DOXYGEN_PROJECT_NAME ${PROJECT_NAME})
    set(DOXYGEN_ENABLE_PREPROCESSING YES)
    set(DOXYGEN_MACRO_EXPANSION YES)
    set(DOXYGEN_EXPAND_ONLY_PREDEF YES)
    set(DOXYGEN_PREDEFINED SCLOG_EXPORT)

    doxygen_add_docs(${PROJECT_NAME}_docs
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sclog/
        ${CMAKE_CURRENT_SOURCE_DIR}/include/platform/posix/sclog/
        ${CMAKE_CURRENT_SOURCE_DIR}/include/platform/linux/sclog/
        ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/mainpage.dox
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        COMMENT "Generating API documentation with Doxygen"
    )
else(DOXYGEN_FOUND)
    message(STATUS "Doxygen need to be installed to generate the doxygen documentation")
endif(DOXYGEN_FOUND)
