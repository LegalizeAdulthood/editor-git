#pragma once

#include <git2.h>

#include <string>

namespace gitpp
{

class Oid
{
public:
    Oid() = default;
    explicit Oid(const git_oid &oid);

    const git_oid *ptr() const { return &m_oid; }
    git_oid *ptr() { return &m_oid; }

    std::string to_string() const;

private:
    git_oid m_oid{};
};

} // namespace gitpp
