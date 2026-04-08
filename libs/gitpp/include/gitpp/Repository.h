#pragma once

#include <gitpp/Git.h>

#include <git2.h>

#include <filesystem>
#include <string>
#include <vector>

namespace gitpp
{

struct CommitInfo
{
    std::string id;
    std::string message;
};

using CommitHistory = std::vector<CommitInfo>;

class Repository
{
public:
    static void create(const std::filesystem::path &path);

    Repository() = delete;
    Repository(const std::filesystem::path &path);
    Repository(const Repository &rhs) = delete;
    Repository(Repository &&rhs) = delete;
    ~Repository();
    Repository &operator=(const Repository &rhs) = delete;
    Repository &operator=(Repository &&rhs) = delete;

    bool is_empty() const;

    void stage_file(const char *path);
    void commit(const char *message);
    CommitHistory get_file_history(const char *path);
    std::string get_file_content(const char *commit_id, const char *path);

    git_repository *handle() const
    {
        return m_handle;
    }

private:
    Git m_git;
    git_repository *m_handle{};
};

} // namespace gitpp
