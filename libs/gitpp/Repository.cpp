#include <gitpp/Repository.h>

#include <gitpp/Commit.h>
#include <gitpp/Config.h>
#include <gitpp/Index.h>
#include <gitpp/Tree.h>

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

    Tree tree{m_handle, tree_id};

    git_signature *signature{};
    check_git_error(git_signature_default(&signature, m_handle));

    Oid commit_id;
    if (is_empty())
    {
        check_git_error(
            git_commit_create_v(commit_id.ptr(), m_handle, "HEAD", signature, signature, nullptr, message, tree.handle(), 0));
    }
    else
    {
        git_object *parent_obj{};
        check_git_error(git_revparse_single(&parent_obj, m_handle, "HEAD"));
        Commit parent{m_handle, git_object_id(parent_obj)};
        git_object_free(parent_obj);

        check_git_error(git_commit_create_v(
            commit_id.ptr(), m_handle, "HEAD", signature, signature, nullptr, message, tree.handle(), 1, parent.handle()));
    }

    git_signature_free(signature);
}

CommitHistory Repository::get_file_history(const char *path)
{
    CommitHistory history;

    if (is_empty())
    {
        return history;
    }

    git_revwalk *walker{};
    check_git_error(git_revwalk_new(&walker, m_handle));
    check_git_error(git_revwalk_push_head(walker));
    git_revwalk_sorting(walker, GIT_SORT_TIME);

    Oid oid;
    while (git_revwalk_next(oid.ptr(), walker) == 0)
    {
        Commit commit{m_handle, oid};

        Tree tree{m_handle, commit.tree_id()};
        Tree parent_tree;
        git_diff *diff{};

        if (commit.parent_count() > 0)
        {
            parent_tree = Tree{m_handle, Commit{m_handle, commit.parent_id(0)}.tree_id()};
        }

        git_diff_tree_to_tree(&diff, m_handle, parent_tree.handle(), tree.handle(), nullptr);

        bool file_changed = false;
        size_t num_deltas = git_diff_num_deltas(diff);
        for (size_t i = 0; i < num_deltas; ++i)
        {
            const git_diff_delta *delta = git_diff_get_delta(diff, i);
            if (delta->new_file.path && strcmp(delta->new_file.path, path) == 0)
            {
                file_changed = true;
                break;
            }
        }

        if (file_changed)
        {
            CommitInfo info;
            info.id = oid.to_string();
            info.message = commit.message();
            history.push_back(std::move(info));
        }

        git_diff_free(diff);
    }

    git_revwalk_free(walker);
    return history;
}

} // namespace gitpp
