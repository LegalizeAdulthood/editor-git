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
        check_git_error(
            git_commit_create_v(commit_id.ptr(), m_handle, "HEAD", signature, signature, nullptr, message, tree, 0));
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

    git_oid oid;
    while (git_revwalk_next(&oid, walker) == 0)
    {
        git_commit *commit{};
        if (git_commit_lookup(&commit, m_handle, &oid) != 0)
        {
            continue;
        }

        git_tree *tree{};
        git_tree *parent_tree{};
        git_diff *diff{};

        git_commit_tree(&tree, commit);

        if (git_commit_parentcount(commit) > 0)
        {
            git_commit *parent{};
            git_commit_parent(&parent, commit, 0);
            git_commit_tree(&parent_tree, parent);
            git_commit_free(parent);
        }

        git_diff_tree_to_tree(&diff, m_handle, parent_tree, tree, nullptr);

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
            char id_str[GIT_OID_SHA1_HEXSIZE + 1];
            git_oid_tostr(id_str, sizeof(id_str), &oid);

            CommitInfo info;
            info.id = id_str;
            info.message = git_commit_message(commit);
            history.push_back(std::move(info));
        }

        git_diff_free(diff);
        git_tree_free(parent_tree);
        git_tree_free(tree);
        git_commit_free(commit);
    }

    git_revwalk_free(walker);
    return history;
}

} // namespace gitpp
