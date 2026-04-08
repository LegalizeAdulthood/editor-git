#include <gitpp/Repository.h>

#include <gitpp/Config.h>
#include <gitpp/Index.h>

#include <stdexcept>

namespace gitpp
{

void Repository::create(const std::filesystem::path &path)
{
    Git git;
    git_repository *repo{};
    constexpr int not_bare{0};
    check_git_error(git_repository_init(&repo, path.string().c_str(), not_bare));
    Config config(repo);
    config.set_string("user.name", "Utah C++ Editor Version");
    config.set_string("user.email", "utahcpp@example.com");
}

Repository::Repository(const std::filesystem::path &path)
{
    check_git_error(git_repository_open(&m_handle, path.string().c_str()));
}

Repository::~Repository()
{
    git_repository_free(m_handle);
}

bool Repository::is_empty() const
{
    return git_repository_is_empty(m_handle) == 1;
}

void Repository::stage_file(const char *path)
{
    Index index{m_handle};
    index.add_bypath(path);
    index.write();
}

void Repository::commit(const char *message)
{
    Index index{m_handle};
    Oid tree_id = index.write_tree();

    git_tree *tree{};
    check_git_error(git_tree_lookup(&tree, m_handle, tree_id.ptr()));

    git_signature *signature{};
    check_git_error(git_signature_default(&signature, m_handle));

    Oid commit_id;
    if (is_empty())
    {
        check_git_error(git_commit_create_v(
            commit_id.ptr(), m_handle, "HEAD", signature, signature, nullptr, message, tree, 0));
    }
    else
    {
        git_object *parent_obj{};
        check_git_error(git_revparse_single(&parent_obj, m_handle, "HEAD"));
        git_commit *parent{};
        check_git_error(git_commit_lookup(&parent, m_handle, git_object_id(parent_obj)));
        git_object_free(parent_obj);

        check_git_error(git_commit_create_v(
            commit_id.ptr(), m_handle, "HEAD", signature, signature, nullptr, message, tree, 1, parent));
        git_commit_free(parent);
    }

    git_signature_free(signature);
    git_tree_free(tree);
}

} // namespace gitpp
