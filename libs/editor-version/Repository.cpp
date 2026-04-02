#include <editor-version/Repository.h>

#include <git2.h>

#include <stdexcept>

namespace version
{

class GitRepository : public Repository
{
public:
    GitRepository(const std::filesystem::path &path)
    {
        if (!std::filesystem::exists(path))
        {
            throw std::runtime_error(path.string() + " does not exist");
        }
    }
    ~GitRepository() override = default;
};

std::shared_ptr<Repository> open_repository(const std::filesystem::path &path)
{
    return std::make_shared<GitRepository>(path);
}

} // namespace version
