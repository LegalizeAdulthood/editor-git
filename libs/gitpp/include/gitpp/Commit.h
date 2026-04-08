#pragma once

#include <gitpp/Git.h>
#include <gitpp/Oid.h>

#include <git2.h>

namespace gitpp
{

class Repository;

class Commit
{
public:
    explicit Commit(git_repository *repo, const Oid &oid);
    explicit Commit(git_repository *repo, const git_oid *oid);
    Commit(const Commit &rhs) = delete;
    Commit(Commit &&rhs) = delete;
    ~Commit();
    Commit &operator=(const Commit &rhs) = delete;
    Commit &operator=(Commit &&rhs) = delete;

    const char *message() const;
    unsigned int parent_count() const;
    Oid parent_id(unsigned int n) const;
    Oid tree_id() const;

    git_commit *handle() const
    {
        return m_handle;
    }

private:
    Git m_git;
    git_commit *m_handle{};
};

} // namespace gitpp
