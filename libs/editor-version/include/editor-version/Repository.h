#pragma once

#include <filesystem>
#include <memory>

namespace version
{

class Repository
{
public:
    virtual ~Repository() = default;

    virtual bool is_empty() const = 0;
};

std::shared_ptr<Repository> open_repository(const std::filesystem::path &path);

}
