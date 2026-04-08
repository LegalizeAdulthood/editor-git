#include <gitpp/RevisionWalker.h>

namespace gitpp
{

RevisionWalker::RevisionWalker(git_repository *repo)
{
    check_git_error(git_revwalk_new(&m_handle, repo));
}

RevisionWalker::~RevisionWalker()
{
    git_revwalk_free(m_handle);
}

void RevisionWalker::push_head()
{
    check_git_error(git_revwalk_push_head(m_handle));
}

void RevisionWalker::sorting(unsigned int sort_mode)
{
    git_revwalk_sorting(m_handle, sort_mode);
}

bool RevisionWalker::next(Oid &oid)
{
    return git_revwalk_next(oid.ptr(), m_handle) == 0;
}

} // namespace gitpp
