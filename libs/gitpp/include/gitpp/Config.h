#pragma once

#include <gitpp/Git.h>

#include <git2.h>

#include <string>

namespace gitpp
{

class Repository;

class Config
{
public:
    explicit Config(git_repository *repo);
    explicit Config(const Repository &repo);
    Config(const Config &rhs) = delete;
    Config(Config &&rhs) = delete;
    ~Config();
    Config &operator=(const Config &rhs) = delete;
    Config &operator=(Config &&rhs) = delete;

    void set_string(const char *name, const char *value);
    std::string get_string(const char *name) const;

private:
    Git m_git;
    git_config *m_handle{};
};

} // namespace gitpp
