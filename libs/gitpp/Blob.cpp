#include <gitpp/Blob.h>

namespace gitpp
{

Blob::Blob(git_repository *repo, const Oid &oid)
{
    check_git_error(git_blob_lookup(&m_handle, repo, oid.ptr()));
}

Blob::~Blob()
{
    git_blob_free(m_handle);
}

const void *Blob::raw_content() const
{
    return git_blob_rawcontent(m_handle);
}

git_object_size_t Blob::raw_size() const
{
    return git_blob_rawsize(m_handle);
}

std::string Blob::content() const
{
    return std::string(static_cast<const char *>(raw_content()), raw_size());
}

} // namespace gitpp
