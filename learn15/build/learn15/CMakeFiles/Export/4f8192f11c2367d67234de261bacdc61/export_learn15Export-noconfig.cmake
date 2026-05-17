#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "learn15::mcl_core" for configuration ""
set_property(TARGET learn15::mcl_core APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(learn15::mcl_core PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libmcl_core.so"
  IMPORTED_SONAME_NOCONFIG "libmcl_core.so"
  )

list(APPEND _cmake_import_check_targets learn15::mcl_core )
list(APPEND _cmake_import_check_files_for_learn15::mcl_core "${_IMPORT_PREFIX}/lib/libmcl_core.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
