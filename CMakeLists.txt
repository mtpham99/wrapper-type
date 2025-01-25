cmake_minimum_required(VERSION 3.30)

# https://www.kitware.com/import-std-in-cmake-3-30
# https://github.com/Kitware/CMake/blob/v3.31.3/Help/dev/experimental.rst
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
set(CMAKE_CXX_MODULE_STD ON)

project(
  wrapper-type
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_library(wrapper)
add_library(wrapper::wrapper ALIAS wrapper)
target_sources(
  wrapper
  PUBLIC FILE_SET
         CXX_MODULES
         BASE_DIRS
         ${PROJECT_SOURCE_DIR}/src
         FILES
         ${PROJECT_SOURCE_DIR}/src/wrapper.cppm
         ${PROJECT_SOURCE_DIR}/src/wrap.cppm
         ${PROJECT_SOURCE_DIR}/src/ops.cppm
         ${PROJECT_SOURCE_DIR}/src/utils.cppm)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  add_subdirectory(tests)
endif()
