#pragma once

#include <gitpp/Git.h>

#include <git2.h>

namespace gitpp
{

class Tree;

class Diff
{
public:
    Diff(git_repository *repo, const Tree &old_tree, const Tree &new_tree);
    Diff(const Diff &rhs) = delete;
    Diff(Diff &&rhs) = delete;
    ~Diff();
    Diff &operator=(const Diff &rhs) = delete;
    Diff &operator=(Diff &&rhs) = delete;

    bool contains_file(const char *path) const;

private:
    Git m_git;
    git_diff *m_handle{};
};

} // namespace gitpp
