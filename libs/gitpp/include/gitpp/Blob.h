#pragma once

#include <gitpp/Git.h>
#include <gitpp/Oid.h>

#include <git2.h>

#include <string>

namespace gitpp
{

class Blob
{
public:
    Blob(git_repository *repo, const Oid &oid);
    Blob(const Blob &rhs) = delete;
    Blob(Blob &&rhs) = delete;
    ~Blob();
    Blob &operator=(const Blob &rhs) = delete;
    Blob &operator=(Blob &&rhs) = delete;

    const void *raw_content() const;
    git_object_size_t raw_size() const;
    std::string content() const;

    git_blob *handle() const
    {
        return m_handle;
    }

private:
    Git m_git;
    git_blob *m_handle{};
};

} // namespace gitpp
