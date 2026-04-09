add_library(editor-version
    include/editor-version/Repository.h
    Repository.cpp
)
target_include_directories(editor-version PUBLIC include)
target_link_libraries(editor-version PRIVATE gitpp)
target_folder(editor-version "Libraries")
