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

} // namespace gitpp
