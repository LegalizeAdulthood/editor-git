#pragma once

#include <gitpp/Git.h>

#include <git2.h>

namespace gitpp
{

class Signature
{
public:
    explicit Signature(git_repository *repo);
    Signature(const Signature &rhs) = delete;
    Signature(Signature &&rhs) = delete;
    ~Signature();
    Signature &operator=(const Signature &rhs) = delete;
    Signature &operator=(Signature &&rhs) = delete;

    git_signature *handle() const
    {
        return m_handle;
    }

private:
    Git m_git;
    git_signature *m_handle{};
};

} // namespace gitpp
