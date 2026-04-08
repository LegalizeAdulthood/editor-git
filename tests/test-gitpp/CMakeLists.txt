include(GoogleTest)

find_package(Git REQUIRED)
find_package(GTest CONFIG REQUIRED)

set(TEST_DATA_DIR "${CMAKE_CURRENT_BINARY_DIR}/test_data")
set(TEST_SCRATCH_DIR "${TEST_DATA_DIR}/scratch")
configure_file("test_data.h.in" "include/test_data.h")

add_executable("test-gitpp"
    "test_data.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/test_data.h"
    "Repository_test.cpp")
source_group("CMake Templates" FILES "test_data.h.in")
target_include_directories("test-gitpp" PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/include")
target_link_libraries("test-gitpp" PUBLIC GTest::gtest_main gitpp)
target_folder("test-gitpp" "Tests")

gtest_discover_tests("test-gitpp")
