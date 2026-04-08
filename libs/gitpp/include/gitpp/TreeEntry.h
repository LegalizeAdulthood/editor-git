#pragma once

#include <gitpp/Git.h>
#include <gitpp/Oid.h>

#include <git2.h>

namespace gitpp
{

class Tree;

class TreeEntry
{
public:
    TreeEntry(const Tree &tree, const char *path);
    TreeEntry(const TreeEntry &rhs) = delete;
    TreeEntry(TreeEntry &&rhs) = delete;
    ~TreeEntry();
    TreeEntry &operator=(const TreeEntry &rhs) = delete;
    TreeEntry &operator=(TreeEntry &&rhs) = delete;

    Oid id() const;

    git_tree_entry *handle() const
    {
        return m_handle;
    }

private:
    Git m_git;
    git_tree_entry *m_handle{};
};

} // namespace gitpp
