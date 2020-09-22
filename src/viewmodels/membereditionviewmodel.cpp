#include <QtConcurrent/QtConcurrent>

#include "membereditionviewmodel.hpp"
#include "databasemanager.hpp"

MemberEditionViewModel::MemberEditionViewModel(QObject *parent)
    : QObject(parent)
{
    m_isWorking = false;
    m_appDatabase = QSqlDatabase::database(DATABASE_CONNECTION_NAME);

    connect(this, &MemberEditionViewModel::projectCreated, &m_projectModel, &ProjectModel::insertProject);
    connect(this, &MemberEditionViewModel::projectDeleted, &m_projectModel, &ProjectModel::deleteProject);
}

bool MemberEditionViewModel::isWorking() const
{
    return m_isWorking;
}

void MemberEditionViewModel::createMember(const QString &name, const QString &job)
{
    setIsWorking(true);
    MemberEditionViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, name, job]()
    {
        Member *member = new Member(name, job);
        viewModel->m_memberDao.setDatabase(viewModel->m_appDatabase);
        viewModel->m_projectDao.setDatabase(viewModel->m_appDatabase);
        viewModel->m_memberDao.createOne(member);
        QList<Project*> projects = viewModel->m_projectModel.projects();
        foreach (Project* project, projects)
        {
            project->setMemberId(member->guid());
        }
        viewModel->m_projectDao.createAll(projects);
        emit viewModel->memberCreated(member);
        viewModel->setIsWorking(false);
    });
}

void MemberEditionViewModel::createProject(const QString &name, const QString &description)
{
    setIsWorking(true);
    MemberEditionViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, name, description]()
    {
        Project *project = new Project(name, description);
        emit viewModel->projectCreated(project);
        viewModel->setIsWorking(false);
    });
}

void MemberEditionViewModel::deleteProject(const quint64 &guid, const quint32 &index)
{
    setIsWorking(true);
    MemberEditionViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, guid, index]()
    {
        emit viewModel->projectDeleted(guid, index);
        viewModel->setIsWorking(false);
    });
}

QObject* MemberEditionViewModel::projectModel()
{
    return dynamic_cast<QObject*>(&m_projectModel);
}

void MemberEditionViewModel::setIsWorking(const bool &isWorking)
{
    if(m_isWorking != isWorking)
    {
        m_isWorking = isWorking;
        emit isWorkingChanged(m_isWorking);
    }
}
