 find_package(libgit2 CONFIG REQUIRED)

add_library(gitpp
    include/gitpp/Commit.h
    Commit.cpp
    include/gitpp/Config.h
    Config.cpp
    include/gitpp/Git.h
    include/gitpp/Index.h
    Index.cpp
    include/gitpp/Oid.h
    Oid.cpp
    include/gitpp/Repository.h
    Repository.cpp
)
target_include_directories(gitpp PUBLIC include)
target_link_libraries(gitpp PUBLIC libgit2::libgit2package)
target_folder(gitpp "Libraries")
