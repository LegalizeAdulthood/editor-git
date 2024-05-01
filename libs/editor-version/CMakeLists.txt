add_library(editor-version
    include/editor-version/editor-version.h
    editor-version.cpp
)
target_include_directories(editor-version PUBLIC include)
target_folder(editor-version "Libraries")
