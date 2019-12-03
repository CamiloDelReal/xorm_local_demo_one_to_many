#include "project.hpp"
#include "member.hpp"

Project::Project(QObject *parent)
    : QObject(parent), XTableModel<Project>()
{
    m_guid = 0;
}

Project::Project(const QString &name, const QString &description, QObject *parent)
    : QObject(parent), XTableModel<Project>()
{
    m_name = name;
    m_description = description;
    m_memberId = 0;
}

Project::Project(const QString &name, const QString &description, const quint64 &memberId, QObject *parent)
    : QObject(parent), XTableModel<Project>()
{
    m_name = name;
    m_description = description;
    m_memberId = memberId;
}

Project::Project(const quint64 &guid, const QString &name, const QString &description, const quint64 &memberId, QObject *parent)
    : QObject(parent), XTableModel<Project>()
{
    m_guid = guid;
    m_name = name;
    m_description = description;
    m_memberId = memberId;
}

Project::Project(const Project &other)
    : QObject(other.parent()), XTableModel<Project>()
{
    m_guid = other.m_guid;
    m_name = other.m_name;
    m_description = other.m_description;
    m_memberId = other.m_memberId;
}

Project& Project::operator=(const Project &other)
{
    m_guid = other.m_guid;
    m_name = other.m_name;
    m_description = other.m_description;
    m_memberId = other.m_memberId;

    setParent(other.parent());

    return *this;
}

quint64 Project::guid() const
{
    return m_guid;
}

QString Project::name() const
{
    return m_name;
}

QString Project::description() const
{
    return m_description;
}

quint64 Project::memberId() const
{
    return m_memberId;
}

void Project::setGuid(const quint64 &guid)
{
    if (m_guid != guid)
    {
        m_guid = guid;
        emit guidChanged(m_guid);
    }
}

void Project::setName(const QString &name)
{
    if (m_name != name)
    {
        m_name = name;
        emit nameChanged(m_name);
    }
}

void Project::setDescription(const QString &description)
{
    if (m_description != description)
    {
        m_description = description;
        emit descriptionChanged(m_description);
    }
}

void Project::setMemberId(const quint64 &memberId)
{
    if (m_memberId != memberId)
    {
        m_memberId = memberId;
        emit memberIdChanged(m_memberId);
    }
}
