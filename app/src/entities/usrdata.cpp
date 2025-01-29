#include "entities/usrdata.h"

UsrData::UsrData(const int id)
    : m_id(id)
{
}

UsrData::UsrData(const QString& username)
    : m_username(username)
{
}

UsrData::UsrData(const int id, const QString& username)
    : m_id(id), m_username(username)
{
}

std::optional<int> UsrData::getId() const
{
    return m_id;
}

const QString& UsrData::getUsername() const
{
    return m_username;
}

void UsrData::setUsername(const QString &username)
{
    m_username = username;
}
