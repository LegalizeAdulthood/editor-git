#pragma once

#include <git2.h>

#include <string>

namespace gitpp
{

class Commit;
class Signature;
class Tree;

class Oid
{
public:
    Oid() = default;
    explicit Oid(const git_oid &oid);

    void create_commit(git_repository *repo, const Signature &signature, const char *message, const Tree &tree);
    void create_commit(
        git_repository *repo, const Signature &signature, const char *message, const Tree &tree, const Commit &parent);

    const git_oid *ptr() const
    {
        return &m_oid;
    }
    git_oid *ptr()
    {
        return &m_oid;
    }

    std::string to_string() const;

private:
    git_oid m_oid{};
};

} // namespace gitpp
