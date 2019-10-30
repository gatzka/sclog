cmake_minimum_required(VERSION 3.11)
project(sclog-all C)

if(CMAKE_CONFIGURATION_TYPES)
  if(NOT "MemorySanitizer" IN_LIST CMAKE_CONFIGURATION_TYPES)
    list(APPEND CMAKE_CONFIGURATION_TYPES MemorySanitizer)
  endif()
  if(NOT "AddressSanitizer" IN_LIST CMAKE_CONFIGURATION_TYPES)
    list(APPEND CMAKE_CONFIGURATION_TYPES AddressSanitizer)
  endif()
  if(NOT "LeakSanitizer" IN_LIST CMAKE_CONFIGURATION_TYPES)
    list(APPEND CMAKE_CONFIGURATION_TYPES LeakSanitizer)
  endif()
  if(NOT "UndefinedBehaviorSanitizer" IN_LIST CMAKE_CONFIGURATION_TYPES)
    list(APPEND CMAKE_CONFIGURATION_TYPES UndefinedBehaviorSanitizer)
  endif()
  if(NOT "Coverage" IN_LIST CMAKE_CONFIGURATION_TYPES)
    list(APPEND CMAKE_CONFIGURATION_TYPES Coverage)
  endif()
else()
  set(allowableBuildTypes Debug Release MemorySanitizer AddressSanitizer LeakSanitizer Coverage)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY
  STRINGS "${allowableBuildTypes}")
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
  elseif(NOT CMAKE_BUILD_TYPE IN_LIST allowableBuildTypes)
    message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
  endif()
endif()

include(CTest)

add_subdirectory(src)
add_subdirectory(tests)
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
   ${PROJECT_SOURCE_DIR}/tests/*.c
   ${PROJECT_SOURCE_DIR}/tests/*.h
)

add_custom_target(sclog-format SOURCES ${FILES_TO_FORMAT})
AddClangFormat(sclog-format)
