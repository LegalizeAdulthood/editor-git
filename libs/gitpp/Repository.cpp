#include <gitpp/Repository.h>

#include <stdexcept>

namespace gitpp
{

Repository::Repository(const std::filesystem::path &path)
{
    check_git_error(git_repository_open(&m_repository, path.string().c_str()));
}

Repository::~Repository()
{
    git_repository_free(m_repository);
}

bool Repository::is_empty() const
{
    return git_repository_is_empty(m_repository) == 1;
}

} // namespace gitpp
