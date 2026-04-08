#include <gitpp/Repository.h>

#include <gitpp/Config.h>

#include <stdexcept>

namespace gitpp
{

void Repository::create(const std::filesystem::path &path)
{
    Git git;
    git_repository *repo{};
    constexpr int not_bare{0};
    check_git_error(git_repository_init(&repo, path.string().c_str(), not_bare));
    Config config(repo);
    config.set_string("user.name", "Utah C++ Editor Version");
    config.set_string("user.email", "utahcpp@example.com");
}

Repository::Repository(const std::filesystem::path &path)
{
    check_git_error(git_repository_open(&m_handle, path.string().c_str()));
}

Repository::~Repository()
{
    git_repository_free(m_handle);
}

bool Repository::is_empty() const
{
    return git_repository_is_empty(m_handle) == 1;
}

} // namespace gitpp
