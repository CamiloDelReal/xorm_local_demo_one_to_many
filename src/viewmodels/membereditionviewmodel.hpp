#ifndef MEMBEREDITIONVIEWMODEL_HPP
#define MEMBEREDITIONVIEWMODEL_HPP

#include <QObject>

#include "xdao.hpp"
#include "member.hpp"
#include "projectmodel.hpp"


class MemberEditionViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isWorking READ isWorking NOTIFY isWorkingChanged)
    Q_PROPERTY(QObject* projectModel READ projectModel NOTIFY projectModelChanged)

public:
    explicit MemberEditionViewModel(QObject *parent = nullptr);

    bool isWorking() const;
    QObject* projectModel();

    Q_INVOKABLE void createMember(const QString &name, const QString &job);
    Q_INVOKABLE void createProject(const QString &name, const QString &description);
    Q_INVOKABLE void deleteProject(const quint64 &guid, const quint32 &index);

signals:
    void isWorkingChanged(const bool &isWorking);
    void projectModelChanged(QObject* projectModel);

    void memberCreated(Member *member);
    void projectCreated(Project *project);
    void projectDeleted(const quint64 &guid, const quint32 &index);

private:
    bool m_isWorking;
    ProjectModel m_projectModel;
    QSqlDatabase m_appDatabase;
    XDao<Member> m_memberDao;
    XDao<Project> m_projectDao;

private slots:
    void setIsWorking(const bool &isWorking);
};

#endif // MEMBEREDITIONVIEWMODEL_HPP
