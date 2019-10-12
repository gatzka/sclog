#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "sclog::sclog" for configuration "Debug"
set_property(TARGET sclog::sclog APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(sclog::sclog PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/sclog.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS sclog::sclog )
list(APPEND _IMPORT_CHECK_FILES_FOR_sclog::sclog "${_IMPORT_PREFIX}/lib/sclog.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
