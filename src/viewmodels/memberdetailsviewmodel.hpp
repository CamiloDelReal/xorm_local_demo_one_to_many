#ifndef MEMBERDETAILSVIEWMODEL_HPP
#define MEMBERDETAILSVIEWMODEL_HPP

#include <QObject>

#include "xdao.hpp"
#include "member.hpp"
#include "projectmodel.hpp"


class MemberDetailsViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isWorking READ isWorking NOTIFY isWorkingChanged)
    Q_PROPERTY(Member* currentMember READ currentMember NOTIFY currentMemberChanged)
    Q_PROPERTY(QObject* projectModel READ projectModel NOTIFY projectModelChanged)

public:
    explicit MemberDetailsViewModel(QObject *parent = nullptr);
    ~MemberDetailsViewModel();

    bool isWorking() const;
    Member* currentMember() const;
    QObject* projectModel();

    Q_INVOKABLE void readMember(const quint64 &guid);

signals:
    void isWorkingChanged(const bool &isWorking);
    void currentMemberChanged(Member* currentMember);

    void projectModelChanged(QObject* projectModel);
    void projectsReset(QList<Project*> project);

private:
    bool m_isWorking;
    QSqlDatabase m_appDatabase;
    XDao<Member> m_memberDao;
    Member* m_currentMember;
    ProjectModel m_projectModel;

private slots:
    void setIsWorking(const bool &isWorking);
};

#endif // MEMBERDETAILSVIEWMODEL_HPP
