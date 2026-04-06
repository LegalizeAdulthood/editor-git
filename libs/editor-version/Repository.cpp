#include <editor-version/Repository.h>

#include <gitpp/Repository.h>

namespace version
{

class GitRepository : public Repository
{
public:
    GitRepository() = delete;
    GitRepository(const std::filesystem::path &path)
        : m_repository(path.string().c_str())
    {
    }
    GitRepository(const GitRepository &rhs) = delete;
    GitRepository(GitRepository &&rhs) = delete;
    ~GitRepository() override = default;
    GitRepository &operator=(const GitRepository &rhs) = delete;
    GitRepository &operator=(GitRepository &&rhs) = delete;

    bool is_empty() const override
    {
        return m_repository.is_empty();
    }

private:
    gitpp::Repository m_repository;
};

std::shared_ptr<Repository> open_repository(const std::filesystem::path &path)
{
    return std::make_shared<GitRepository>(path);
}

} // namespace version
