 find_package(Boost REQUIRED COMPONENTS stl_interfaces)
 find_package(libgit2 CONFIG REQUIRED)

add_library(editor-version
    include/editor-version/Repository.h
    Repository.cpp
)
target_include_directories(editor-version PUBLIC include)
target_link_libraries(editor-version PUBLIC libgit2::libgit2package Boost::stl_interfaces)
target_folder(editor-version "Libraries")
