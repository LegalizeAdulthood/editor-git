#pragma once

#include <gitpp/Git.h>
#include <gitpp/Oid.h>

#include <git2.h>

namespace gitpp
{

class Object
{
public:
    Object(git_repository *repo, const char *spec);
    Object(const Object &rhs) = delete;
    Object(Object &&rhs) = delete;
    ~Object();
    Object &operator=(const Object &rhs) = delete;
    Object &operator=(Object &&rhs) = delete;

    Oid id() const;

    git_object *handle() const
    {
        return m_handle;
    }

private:
    Git m_git;
    git_object *m_handle{};
};

} // namespace gitpp
