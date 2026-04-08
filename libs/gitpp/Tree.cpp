#include <gitpp/Tree.h>

#include <utility>

namespace gitpp
{

Tree::Tree(git_repository *repo, const Oid &oid)
{
    check_git_error(git_tree_lookup(&m_handle, repo, oid.ptr()));
}

Tree::Tree(Tree &&rhs) noexcept :
    m_handle(std::exchange(rhs.m_handle, nullptr))
{
}

Tree::~Tree()
{
    git_tree_free(m_handle);
}

Tree &Tree::operator=(Tree &&rhs) noexcept
{
    if (this != &rhs)
    {
        git_tree_free(m_handle);
        m_handle = std::exchange(rhs.m_handle, nullptr);
    }
    return *this;
}

} // namespace gitpp
