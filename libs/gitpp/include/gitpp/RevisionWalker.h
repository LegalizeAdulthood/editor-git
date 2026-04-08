#pragma once

#include <gitpp/Git.h>
#include <gitpp/Oid.h>

#include <git2.h>

namespace gitpp
{

class RevisionWalker
{
public:
    explicit RevisionWalker(git_repository *repo);
    RevisionWalker(const RevisionWalker &rhs) = delete;
    RevisionWalker(RevisionWalker &&rhs) = delete;
    ~RevisionWalker();
    RevisionWalker &operator=(const RevisionWalker &rhs) = delete;
    RevisionWalker &operator=(RevisionWalker &&rhs) = delete;

    void push_head();
    void sorting(unsigned int sort_mode);
    bool next(Oid &oid);

private:
    Git m_git;
    git_revwalk *m_handle{};
};

} // namespace gitpp
