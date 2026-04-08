#include <gitpp/Object.h>

namespace gitpp
{

Object::Object(git_repository *repo, const char *spec)
{
    check_git_error(git_revparse_single(&m_handle, repo, spec));
}

Object::~Object()
{
    git_object_free(m_handle);
}

Oid Object::id() const
{
    return Oid(*git_object_id(m_handle));
}

} // namespace gitpp
