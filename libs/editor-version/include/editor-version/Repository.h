#pragma once

#include <filesystem>
#include <memory>

namespace version
{

class Repository
{
public:
    virtual ~Repository() = default;
};

std::shared_ptr<Repository> open_repository(const std::filesystem::path &path);

}
