#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace version
{

struct Commit
{
    std::string id;
    std::string message;
    std::string timestamp;
};

using History = std::vector<Commit>;

class Repository
{
public:
    virtual ~Repository() = default;

    virtual bool is_empty() const = 0;

    virtual std::string get_config_string(const char *name) = 0;

    virtual void commit_file(const char *name, const char *message) = 0;

    virtual History get_file_history(const char *name) = 0;

    virtual std::string get_file_content(const char *commit_id, const char *name) = 0;
};

using RepositoryPtr = std::shared_ptr<Repository>;

RepositoryPtr open_repository(const std::filesystem::path &path);
RepositoryPtr create_repository(const std::filesystem::path &path);

} // namespace version
