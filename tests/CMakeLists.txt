find_package(doctest QUIET)
if(doctest_FOUND)
  message("Found system installed \"doctest\". Using system installed library.")
else()
  message(STATUS "\"doctest\" not installed. Fetching from GitHub.")
  include(FetchContent)
  FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
    GIT_SHALLOW TRUE)
  FetchContent_MakeAvailable(doctest)
  list(APPEND CMAKE_MODULE_PATH ${doctest_SOURCE_DIR}/scripts/cmake/)
endif()

add_executable(wrapper_tests)
target_sources(
  wrapper_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_tests.cpp)
target_link_libraries(wrapper_tests PRIVATE doctest::doctest wrapper::wrapper)

include(doctest)
doctest_discover_tests(wrapper_tests)
