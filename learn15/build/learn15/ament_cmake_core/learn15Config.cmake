# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_learn15_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED learn15_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(learn15_FOUND FALSE)
  elseif(NOT learn15_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(learn15_FOUND FALSE)
  endif()
  return()
endif()
set(_learn15_CONFIG_INCLUDED TRUE)

# output package information
if(NOT learn15_FIND_QUIETLY)
  message(STATUS "Found learn15: 0.0.0 (${learn15_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'learn15' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT learn15_DEPRECATED_QUIET)
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(learn15_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "ament_cmake_export_targets-extras.cmake;ament_cmake_export_dependencies-extras.cmake")
foreach(_extra ${_extras})
  include("${learn15_DIR}/${_extra}")
endforeach()
