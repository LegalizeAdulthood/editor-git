 find_package(Boost REQUIRED COMPONENTS stl_interfaces)

add_library(editor-version
    include/editor-version/Repository.h
    Repository.cpp
)
target_include_directories(editor-version PUBLIC include)
target_link_libraries(editor-version PUBLIC gitpp Boost::stl_interfaces)
target_folder(editor-version "Libraries")
