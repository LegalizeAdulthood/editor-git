include(GoogleTest)

find_package(GTest CONFIG REQUIRED)

set(TEST_EXISTING_REPOSITORY "${CMAKE_CURRENT_BINARY_DIR}/test_repo")
set(TEST_NONEXISTING_REPOSITORY "${CMAKE_CURRENT_BINARY_DIR}/bogus_repo")
file(MAKE_DIRECTORY "${TEST_EXISTING_REPOSITORY}")
file(REMOVE_RECURSE "${TEST_NONEXISTING_REPOSITORY}")
configure_file("test_data.h.in" "include/test_data.h")

add_executable("test-editor-version"
    "test_data.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/test_data.h"
    "Repository_test.cpp")
source_group("CMake Templates" FILES "test_data.h.in")
target_include_directories("test-editor-version" PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/include")
target_link_libraries("test-editor-version" PUBLIC GTest::gtest_main editor-version)
target_folder("test-editor-version" "Tests")

gtest_discover_tests("test-editor-version")
