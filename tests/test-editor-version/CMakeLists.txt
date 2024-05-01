include(GoogleTest)

find_package(GTest CONFIG REQUIRED)

add_executable(test-editor-version test.cpp)
target_link_libraries(test-editor-version PUBLIC GTest::gtest_main editor-version)
target_folder(test-editor-version "Tests")

gtest_discover_tests(test-editor-version)
