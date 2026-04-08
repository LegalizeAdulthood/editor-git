#pragma once

#include <git2.h>

namespace gitpp
{

class Oid
{
public:
    Oid() = default;
    explicit Oid(const git_oid &oid);

    const git_oid *ptr() const { return &m_oid; }
    git_oid *ptr() { return &m_oid; }

private:
    git_oid m_oid{};
};

} // namespace gitpp
