#include <editor-version/Repository.h>

#include <gitpp/Config.h>
#include <gitpp/Repository.h>

#include <string>

namespace
{

class GitRepository : public version::Repository
{
public:
    GitRepository() = delete;
    GitRepository(const std::filesystem::path &path);
    GitRepository(const GitRepository &rhs) = delete;
    GitRepository(GitRepository &&rhs) = delete;
    ~GitRepository() override = default;
    GitRepository &operator=(const GitRepository &rhs) = delete;
    GitRepository &operator=(GitRepository &&rhs) = delete;

    bool is_empty() const override
    {
        return m_repository.is_empty();
    }

    std::string get_config_string(const char *name) override;

    void commit_file(const char *name, const char *message) override;

    version::History get_file_history(const char *name) override;

    std::string get_file_content(const char *commit_id, const char *name) override;

private:
    gitpp::Repository m_repository;
};

GitRepository::GitRepository(const std::filesystem::path &path) :
    m_repository(path.string().c_str())
{
}

std::string GitRepository::get_config_string(const char *name)
{
    gitpp::Config config{m_repository};
    return config.get_string(name);
}

void GitRepository::commit_file(const char *name, const char *message)
{
    m_repository.stage_file(name);
    m_repository.commit(message);
}

version::History GitRepository::get_file_history(const char *name)
{
    gitpp::CommitHistory gitpp_history = m_repository.get_file_history(name);
    version::History history;
    history.reserve(gitpp_history.size());
    for (const auto &commit : gitpp_history)
    {
        history.push_back({commit.id, commit.message});
    }
    return history;
}

std::string GitRepository::get_file_content(const char *commit_id, const char *name)
{
    return m_repository.get_file_content(commit_id, name);
}

} // namespace

namespace version
{

RepositoryPtr open_repository(const std::filesystem::path &path)
{
    return std::make_shared<GitRepository>(path);
}

RepositoryPtr create_repository(const std::filesystem::path &path)
{
    gitpp::Repository::create(path);
    return open_repository(path);
}

} // namespace version
