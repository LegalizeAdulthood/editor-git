#include <gitpp/Oid.h>

#include <gitpp/Commit.h>
#include <gitpp/Signature.h>
#include <gitpp/Tree.h>

namespace gitpp
{

Oid::Oid(const git_oid &oid) :
    m_oid(oid)
{
}

void Oid::create_commit(git_repository *repo, const Signature &signature, const char *message, const Tree &tree)
{
    check_git_error(git_commit_create_v(
        &m_oid, repo, "HEAD", signature.handle(), signature.handle(), nullptr, message, tree.handle(), 0));
}

void Oid::create_commit(
    git_repository *repo, const Signature &signature, const char *message, const Tree &tree, const Commit &parent)
{
    check_git_error(git_commit_create_v(&m_oid, repo, "HEAD", signature.handle(), signature.handle(), nullptr, message,
        tree.handle(), 1, parent.handle()));
}

std::string Oid::to_string() const
{
    char id_str[GIT_OID_SHA1_HEXSIZE + 1];
    git_oid_tostr(id_str, sizeof(id_str), &m_oid);
    return id_str;
}

} // namespace gitpp
