#include <gitpp/TreeEntry.h>

#include <gitpp/Tree.h>

namespace gitpp
{

TreeEntry::TreeEntry(const Tree &tree, const char *path)
{
    check_git_error(git_tree_entry_bypath(&m_handle, tree.handle(), path));
}

TreeEntry::~TreeEntry()
{
    git_tree_entry_free(m_handle);
}

Oid TreeEntry::id() const
{
    return Oid(*git_tree_entry_id(m_handle));
}

} // namespace gitpp
