#include <gitpp/Commit.h>

#include <gitpp/Repository.h>

#include <ctime>
#include <iomanip>
#include <sstream>

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

std::string Commit::time_str() const
{
    git_time_t time = git_commit_time(m_handle);
    std::time_t t = static_cast<std::time_t>(time);
    std::tm local_tm{};
#ifdef _WIN32
    localtime_s(&local_tm, &t);
#else
    localtime_r(&t, &local_tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

} // namespace gitpp
