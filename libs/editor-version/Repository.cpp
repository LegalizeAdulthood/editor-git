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

    Iterator begin() override
    {
        return {};
    }
    Iterator end() override
    {
        return {};
    }

private:
    gitpp::Repository m_repository;
};

Repository::Iterator::Iterator() :
    Iterator{nullptr}
{
}

Repository::Iterator::Iterator(Repository *repository) :
    m_repository(repository)
{
}

Commit Repository::Iterator::operator*() const noexcept
{
    return {};
}

Repository::Iterator &Repository::Iterator::operator+=(std::ptrdiff_t count) noexcept
{
    return *this;
}

Repository::Iterator::difference_type Repository::Iterator::operator-(const Iterator &other) const
{
    return 0;
}

std::shared_ptr<Repository> open_repository(const std::filesystem::path &path)
{
    return std::make_shared<GitRepository>(path);
}

} // namespace version
