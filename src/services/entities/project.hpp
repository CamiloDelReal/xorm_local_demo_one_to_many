#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <QObject>

#include "xtablemodel.hpp"


class Member;

class Project : public QObject, public XTableModel<Project>
{
    Q_OBJECT

    Q_PROPERTY(quint64 guid READ guid WRITE setGuid NOTIFY guidChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(quint64 memberId READ memberId WRITE setMemberId NOTIFY memberIdChanged)

    X_TABLE_NAME("projects")
    X_TABLE_FIELDS(X_FIELD(guid, X_PRIMARY_KEY),
                   X_FIELD(name),
                   X_FIELD(description),
                   X_FIELD(memberId, "member_id", X_FOREIGN_KEY(Member, X_CASCADE, X_CASCADE)))

public:
    explicit Project(QObject *parent = nullptr);
    Project(const QString &name, const QString &description, QObject *parent = nullptr);
    Project(const QString &name, const QString &description, const quint64 &memberId, QObject *parent = nullptr);
    Project(const quint64 &guid, const QString &name, const QString &description, const quint64 &memberId, QObject *parent = nullptr);
    Project(const Project &other);

    Project& operator=(const Project &other);

    quint64 guid() const;
    QString name() const;
    QString description() const;
    quint64 memberId() const;

public slots:
    void setGuid(const quint64 &guid);
    void setName(const QString &name);
    void setDescription(const QString &description);
    void setMemberId(const quint64 &memberId);

signals:
    void guidChanged(const quint64 &guid);
    void nameChanged(const QString &name);
    void descriptionChanged(const QString &description);
    void memberIdChanged(const quint64 &memberId);

private:
    quint64 m_guid;
    QString m_name;
    QString m_description;
    quint64 m_memberId;
};


#include "member.hpp"

#endif // PROJECT_HPP

