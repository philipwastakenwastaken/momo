cmake_minimum_required(VERSION 3.12)

project(momo CXX)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)


# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# Enable cache system
include(cmake/Cache.cmake)

# Standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

option(MOMO_ENABLE_TESTING "Enable Test Builds" ON)

add_subdirectory(lib)

include(cmake/StaticAnalyzers.cmake)
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# To slience warnings from libraries
include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/lib/spdlog/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

if(MOMO_ENABLE_TESTING)
  enable_testing()
  message("Building Tests")
  add_subdirectory(test)
endif()

add_subdirectory(src)

# For running using "make run"
add_custom_target(run
    COMMAND momo
    DEPENDS momo
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)