#include <gitpp/Signature.h>

namespace gitpp
{

Signature::Signature(git_repository *repo)
{
    check_git_error(git_signature_default(&m_handle, repo));
}

Signature::~Signature()
{
    git_signature_free(m_handle);
}

} // namespace gitpp
