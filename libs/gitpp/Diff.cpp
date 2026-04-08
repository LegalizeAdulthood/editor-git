#include <gitpp/Diff.h>

#include <gitpp/Tree.h>

#include <cstring>

namespace gitpp
{

Diff::Diff(git_repository *repo, const Tree &old_tree, const Tree &new_tree)
{
    check_git_error(git_diff_tree_to_tree(&m_handle, repo, old_tree.handle(), new_tree.handle(), nullptr));
}

Diff::~Diff()
{
    git_diff_free(m_handle);
}

bool Diff::contains_file(const char *path) const
{
    size_t count = git_diff_num_deltas(m_handle);
    for (size_t i = 0; i < count; ++i)
    {
        const git_diff_delta *delta = git_diff_get_delta(m_handle, i);
        if (delta->new_file.path && strcmp(delta->new_file.path, path) == 0)
        {
            return true;
        }
    }
    return false;
}

} // namespace gitpp
