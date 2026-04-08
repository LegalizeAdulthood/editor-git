#include <gitpp/Commit.h>

#include <gitpp/Repository.h>

namespace gitpp
{

Commit::Commit(git_repository *repo, const Oid &oid)
{
    check_git_error(git_commit_lookup(&m_handle, repo, oid.ptr()));
}

Commit::Commit(git_repository *repo, const git_oid *oid)
{
    check_git_error(git_commit_lookup(&m_handle, repo, oid));
}

Commit::~Commit()
{
    git_commit_free(m_handle);
}

const char *Commit::message() const
{
    return git_commit_message(m_handle);
}

unsigned int Commit::parent_count() const
{
    return git_commit_parentcount(m_handle);
}

Oid Commit::parent_id(unsigned int n) const
{
    return Oid(*git_commit_parent_id(m_handle, n));
}

Oid Commit::tree_id() const
{
    return Oid(*git_commit_tree_id(m_handle));
}

} // namespace gitpp
