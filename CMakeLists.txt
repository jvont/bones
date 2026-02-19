cmake_minimum_required(VERSION 3.14..3.21)
project(bones VERSION 0.1
              DESCRIPTION "bones"
              LANGUAGES CXX)

# ======== Project Configuration ========

# TODO: add switches for different backends
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  # enable BUILD_TESTING
  option(BUILD_TESTING "Build testing library." ON)
  include(CTest)
  
endif()

# ======== CMake Includes ========

# include FetchContent
include(FetchContent)

# include additional FindModule.cmake files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# copy given resources to a target output directory
include(target_configure_files)

# ======== Third-Party ========

# pull in third-party libraries/submodule directories
add_subdirectory(extern)

# ======== Main Library ========

# build main library/link third-party libs
add_subdirectory(bones)

# ======== Testing ========

# sandbox app executable
add_subdirectory(app)

# build testing library/executable
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) AND BUILD_TESTING)
  add_subdirectory(tests)
endif()

# ======== Debug ========

# display possible output config types
# message("Configuration types = ${CMAKE_CONFIGURATION_TYPES}")

# display supported cxx compiler features
# message("Supported features = ${CMAKE_CXX_COMPILE_FEATURES}")
