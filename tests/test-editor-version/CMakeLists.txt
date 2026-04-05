include(GoogleTest)

find_package(Git REQUIRED)
find_package(GTest CONFIG REQUIRED)

set(TEST_DATA_DIR "${CMAKE_CURRENT_BINARY_DIR}/test_data")
set(TEST_EXISTING_REPOSITORY "${TEST_DATA_DIR}/test_repo")
set(TEST_EXISTING_EMPTY_REPOSITORY "${TEST_DATA_DIR}/test_empty_repo")
set(TEST_NON_EXISTING_REPOSITORY "${TEST_DATA_DIR}/bogus_repo")
configure_file("test_data.h.in" "include/test_data.h")

file(REMOVE_RECURSE "${TEST_DATA_DIR}}")
file(MAKE_DIRECTORY "${TEST_EXISTING_EMPTY_REPOSITORY}")
file(MAKE_DIRECTORY "${TEST_NON_EXISTING_REPOSITORY}")
execute_process(COMMAND "${GIT_EXECUTABLE}" "init"
    WORKING_DIRECTORY "${TEST_EXISTING_EMPTY_REPOSITORY}"
    COMMAND_ERROR_IS_FATAL ANY)

add_executable("test-editor-version"
    "test_data.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/test_data.h"
    "Repository_test.cpp")
source_group("CMake Templates" FILES "test_data.h.in")
target_include_directories("test-editor-version" PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/include")
target_link_libraries("test-editor-version" PUBLIC GTest::gtest_main editor-version)
target_folder("test-editor-version" "Tests")

gtest_discover_tests("test-editor-version")
