#include "application.h"

Application::Application(int &argc, char **argv)
    : QGuiApplication(argc, argv)
{
    qmlRegisterType<Notification>("org.heera.NotificationDaemon", 1, 0, "Notification");
    qmlRegisterType<NotificationManager>("org.heera.NotificationDaemon", 1, 0, "NotificationManager");
    qmlRegisterType<QmlNotificationBase>("org.heera.NotificationDaemon", 1, 0, "NotificationBase");
    
    m_engine.addImageProvider(QStringLiteral("icontheme"), new IconThemeProvider());
    m_engine.addImportPath("qrc:/");
    m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
}

