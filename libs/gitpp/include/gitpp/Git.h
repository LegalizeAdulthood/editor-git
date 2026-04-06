#pragma once

#include <git2.h>

#include <stdexcept>

namespace gitpp
{

inline void check_git_error(int result)
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

} // namespace gitpp
