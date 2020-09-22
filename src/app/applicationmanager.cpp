#include <QtQml>
#include <QStandardPaths>

#include "applicationmanager.hpp"
#include "pathutils.hpp"
#include "xdatabase.hpp"

#include "memberlistingviewmodel.hpp"
#include "membereditionviewmodel.hpp"
#include "memberdetailsviewmodel.hpp"


ApplicationManager::ApplicationManager(QObject *parent)
    : MobileManager(parent)
{
}

void ApplicationManager::addContextProperty(QQmlEngine *engine, QQmlContext *context)
{
    m_engine = engine;

    //Register singletons
    qmlRegisterSingletonType(QUrl(QLatin1String("qrc:/qml/XMaterialControls.qml")), "XApps.XMaterialControls", 1, 0, "XMaterialControls");

    //Link C++ objects with QML
    context->setContextProperty("ApplicationManagerObj", this);
    context->setContextProperty("ApplicationSettingsObj", &m_applicationSettings);

    //Register data types
    qRegisterMetaType<Member>("Member");
    qRegisterMetaType<QList<Member*>>("QList<Member*>");
    qmlRegisterType<MemberListingViewModel>("XApps.XOrmDemoOneToMany", 1, 0, "MemberListingViewModel");
    qmlRegisterType<MemberEditionViewModel>("XApps.XOrmDemoOneToMany", 1, 0, "MemberEditionViewModel");
    qmlRegisterType<MemberDetailsViewModel>("XApps.XOrmDemoOneToMany", 1, 0, "MemberDetailsViewModel");
}

void ApplicationManager::initialize()
{
    m_databaseManager.initialize();
}

void ApplicationManager::onAboutToQuit()
{
    m_applicationSettings.saveSettings();
}

void ApplicationManager::onApplicationStateChanged(Qt::ApplicationState applicationState)
{
    if(applicationState == Qt::ApplicationState::ApplicationSuspended)
        onAboutToQuit();
}
