#include <gitpp/Index.h>

#include <gitpp/Repository.h>

namespace gitpp
{

Index::Index(git_repository *repo)
{
    check_git_error(git_repository_index(&m_handle, repo));
}

Index::Index(const Repository &repo) :
    Index(repo.handle())
{
}

Index::~Index()
{
    git_index_free(m_handle);
}

void Index::add_bypath(const char *path)
{
    check_git_error(git_index_add_bypath(m_handle, path));
}

void Index::write()
{
    check_git_error(git_index_write(m_handle));
}

Oid Index::write_tree()
{
    Oid tree_id;
    check_git_error(git_index_write_tree(tree_id.ptr(), m_handle));
    return tree_id;
}

} // namespace gitpp
