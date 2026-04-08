#include <gitpp/Oid.h>

namespace gitpp
{

Oid::Oid(const git_oid &oid) :
    m_oid(oid)
{
}

std::string Oid::to_string() const
{
    char id_str[GIT_OID_SHA1_HEXSIZE + 1];
    git_oid_tostr(id_str, sizeof(id_str), &m_oid);
    return id_str;
}

} // namespace gitpp
