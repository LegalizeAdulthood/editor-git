add_executable(editor main.cpp)
target_link_libraries(editor PUBLIC editor-version)
target_folder(editor "Tools")
