 find_package(libgit2 CONFIG REQUIRED)

add_library(gitpp
    include/gitpp/Commit.h
    Commit.cpp
    include/gitpp/Config.h
    Config.cpp
    include/gitpp/Diff.h
    Diff.cpp
    include/gitpp/Git.h
    include/gitpp/Index.h
    Index.cpp
    include/gitpp/Object.h
    Object.cpp
    include/gitpp/Oid.h
    Oid.cpp
    include/gitpp/Repository.h
    Repository.cpp
    include/gitpp/RevisionWalker.h
    RevisionWalker.cpp
    include/gitpp/Signature.h
    Signature.cpp
    include/gitpp/Tree.h
    Tree.cpp
    include/gitpp/TreeEntry.h
    TreeEntry.cpp
)
target_include_directories(gitpp PUBLIC include)
target_link_libraries(gitpp PUBLIC libgit2::libgit2package)
target_folder(gitpp "Libraries")
