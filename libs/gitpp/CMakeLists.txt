 find_package(libgit2 CONFIG REQUIRED)

add_library(gitpp
    include/gitpp/Git.h
    include/gitpp/Repository.h
    Repository.cpp
)
target_include_directories(gitpp PUBLIC include)
target_link_libraries(gitpp PUBLIC libgit2::libgit2package)
target_folder(gitpp "Libraries")
