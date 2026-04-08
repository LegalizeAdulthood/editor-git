#pragma once

#include <gitpp/Git.h>

#include <git2.h>

#include <filesystem>

namespace gitpp
{

class Repository
{
public:
    static void create(const std::filesystem::path& path);

    Repository() = delete;
    Repository(const std::filesystem::path &path);
    Repository(const Repository &rhs) = delete;
    Repository(Repository &&rhs) = delete;
    ~Repository();
    Repository &operator=(const Repository &rhs) = delete;
    Repository &operator=(Repository &&rhs) = delete;

    bool is_empty() const;

    git_repository *handle() const
    {
        return m_handle;
    }

private:
    Git m_git;
    git_repository *m_handle{};
};

} // namespace gitpp
