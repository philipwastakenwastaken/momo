# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE
      RelWithDebInfo
      CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
  "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Build type definitions
if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(MOMO_DEBUG)
elseif (CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
    add_compile_definitions(MOMO_RELEASE)
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_definitions(MOMO_DIST)
endif()

# Platform definitions
if(APPLE)
    add_compile_definitions(MOMO_PLATFORM_MACOSX)
elseif(WIN32)
    add_compile_definitions(MOMO_PLATFORM_WINDOWS)
elseif(UNIX)
    add_compile_definitions(MOMO_PLATFORM_LINUX)
endif()


# Prevent linking errors on MSVC by expliciting stating static linkage
if(MSVC)
  set(variables
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_RELEASE
	CMAKE_CXX_FLAGS_RELWITHDEBINFO
	CMAKE_CXX_FLAGS_MINSIZEREL
  )
  foreach(variable ${variables})
	if(${variable} MATCHES "/MD")
	  string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
	endif()
  endforeach()
endif()


# Generate compile_commands.json to make it easier to work with clang based tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(MOMO_ENABLE_LTO "Enable Interprocedural Optimization, aka Link Time Optimization (LTO)" OFF)

if(MOMO_ENABLE_LTO)
  include(CheckIPOSupported)

  check_ipo_supported(
    RESULT
    result
    OUTPUT
    output)
  if(result)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    message(SEND_ERROR "IPO is not supported: ${output}")
  endif()
endif()
