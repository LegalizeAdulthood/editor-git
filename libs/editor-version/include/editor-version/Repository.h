#pragma once

#include <filesystem>
#include <memory>
#include <string>

namespace version
{

struct Commit
{
    std::string message;
};

class Repository
{
public:
    virtual ~Repository() = default;

    virtual bool is_empty() const = 0;

    virtual std::string get_config_string(const char *name) = 0;
};

std::shared_ptr<Repository> open_repository(const std::filesystem::path &path);
std::shared_ptr<Repository> create_repository(const std::filesystem::path &path);

} // namespace version
