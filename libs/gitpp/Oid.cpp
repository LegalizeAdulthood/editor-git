#include <gitpp/Oid.h>

namespace gitpp
{

Oid::Oid(const git_oid &oid) :
    m_oid(oid)
{
}

} // namespace gitpp
