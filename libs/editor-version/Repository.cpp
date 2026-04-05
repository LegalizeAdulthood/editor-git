#include <editor-version/Repository.h>

#include <git2.h>

#include <stdexcept>

namespace version
{

static void check_git_error(int result)
{
    if (result != GIT_OK)
    {
        const git_error *error{git_error_last()};
        throw std::runtime_error(error->message);
    }
}

class Git
{
public:
    Git()
    {
        git_libgit2_init();
    }
    ~Git()
    {
        git_libgit2_shutdown();
    }
};

class GitRepository : public Repository
{
public:
    GitRepository() = delete;
    GitRepository(const std::filesystem::path &path)
    {
        check_git_error(git_repository_open(&m_repository, path.string().c_str()));
    }
    GitRepository(const GitRepository &rhs) = delete;
    GitRepository(GitRepository &&rhs) = delete;
    ~GitRepository() override
    {
        git_repository_free(m_repository);
    }
    GitRepository &operator=(const GitRepository &rhs) = delete;
    GitRepository &operator=(GitRepository &&rhs) = delete;

    bool is_empty() const override
    {
        return git_repository_is_empty(m_repository) == 1;
    }

private:
    Git m_git;
    git_repository *m_repository;
};

std::shared_ptr<Repository> open_repository(const std::filesystem::path &path)
{
    return std::make_shared<GitRepository>(path);
}

} // namespace version
