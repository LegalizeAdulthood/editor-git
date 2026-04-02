find_package(libgit2 CONFIG REQUIRED)

add_library(editor-version
    include/editor-version/editor-version.h
    editor-version.cpp
)
target_include_directories(editor-version PUBLIC include)
target_link_libraries(editor-version PUBLIC libgit2::libgit2package)
target_folder(editor-version "Libraries")
