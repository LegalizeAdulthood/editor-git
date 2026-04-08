#pragma once

#include <gitpp/Git.h>
#include <gitpp/Oid.h>

#include <git2.h>

namespace gitpp
{

class Repository;

class Index
{
public:
    explicit Index(git_repository *repo);
    explicit Index(const Repository &repo);
    Index(const Index &rhs) = delete;
    Index(Index &&rhs) = delete;
    ~Index();
    Index &operator=(const Index &rhs) = delete;
    Index &operator=(Index &&rhs) = delete;

    void add_bypath(const char *path);
    void write();
    Oid write_tree();

private:
    Git m_git;
    git_index *m_handle{};
};

} // namespace gitpp
