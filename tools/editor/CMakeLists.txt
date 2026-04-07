find_package(wxWidgets CONFIG REQUIRED)

add_executable(editor WIN32 main.cpp)
target_link_libraries(editor PUBLIC editor-version wx::core wx::base)
target_folder(editor "Tools")
