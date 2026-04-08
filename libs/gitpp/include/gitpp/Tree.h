#pragma once

#include <gitpp/Git.h>
#include <gitpp/Oid.h>

#include <git2.h>

namespace gitpp
{

class Tree
{
public:
    Tree() = default;
    explicit Tree(git_repository *repo, const Oid &oid);
    Tree(const Tree &rhs) = delete;
    Tree(Tree &&rhs) noexcept;
    ~Tree();
    Tree &operator=(const Tree &rhs) = delete;
    Tree &operator=(Tree &&rhs) noexcept;

    git_tree *handle() const
    {
        return m_handle;
    }
    explicit operator bool() const
    {
        return m_handle != nullptr;
    }

private:
    Git m_git;
    git_tree *m_handle{};
};

} // namespace gitpp
