#include <gitpp/Config.h>

#include <gitpp/Repository.h>

namespace gitpp
{

Config::Config(git_repository *repo)
{
    check_git_error(git_repository_config(&m_handle, repo));
}

Config::Config(const Repository &repo) :
    Config(repo.handle())
{
}

Config::~Config()
{
    git_config_free(m_handle);
}

void Config::set_string(const char *name, const char *value)
{
    check_git_error(git_config_set_string(m_handle, name, value));
}

std::string Config::get_string(const char *name) const
{
    git_buf buffer = GIT_BUF_INIT;
    check_git_error(git_config_get_string_buf(&buffer, m_handle, name));
    return buffer.ptr;
}

} // namespace gitpp
