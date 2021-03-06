#include "processmanager.h"

#include <QCoreApplication>
#include <QFileInfoList>
#include <QFileInfo>
#include <QSettings>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QDir>

ProcessManager::ProcessManager(QObject *parent)
    : QObject(parent)
    , m_completedInit(false)
{
}

ProcessManager::~ProcessManager()
{
    QMapIterator<QString, QProcess *> i(m_systemProcess);
    while (i.hasNext()) {
        i.next();
        QProcess *p = i.value();
        delete p;
    }
}

void ProcessManager::start()
{
    loadBaseProcesses();
}

void ProcessManager::logout()
{
    QMapIterator<QString, QProcess *> i(m_systemProcess);

    while (i.hasNext()) {
        i.next();
        QProcess *p = i.value();
        p->terminate();
    }
    i.toFront();

    while (i.hasNext()) {
        i.next();
        QProcess *p = i.value();
        if (p->state() != QProcess::NotRunning && !p->waitForFinished(2000)) {
            p->kill();
        }
    }

    QCoreApplication::exit(0);
}

void ProcessManager::startProcess(QPair<QString, QStringList> pair) {
    QProcess *process = new QProcess;
    process->setProcessChannelMode(QProcess::ForwardedChannels);
    process->setProgram(pair.first);
    process->setArguments(pair.second);
    process->start();
    process->waitForStarted();

    qDebug() << "Load DE components: " << pair.first << pair.second;

    // Add to map
    if (process->exitCode() == 0) {
        m_autoStartProcess.insert(pair.first, process);
    } else {
        process->deleteLater();
    }
}

void ProcessManager::loadBaseProcesses()
{
    QList<QPair<QString, QStringList>> list;
    list << qMakePair(QString("kglobalaccel5"), QStringList());
    list << qMakePair(QString("kwin_x11"), QStringList());
    list << qMakePair(QString("heera-settings-daemon"), QStringList());
    list << qMakePair(QString("heera-xembedsniproxy"), QStringList());

    for (QPair<QString, QStringList> pair : list) {
        startProcess(pair);
    }
}

void ProcessManager::loadLateProcesses() {
    if (m_completedInit)
        return;
    QList<QPair<QString, QStringList>> list;

    // Desktop components
    list << qMakePair(QString("heera-desktop-daemon"), QStringList());
    list << qMakePair(QString("heera-dock"), QStringList());
    list << qMakePair(QString("heera-launcher"), QStringList());
    list << qMakePair(QString("heera-notification-daemon"), QStringList());
    list << qMakePair(QString("heera-hotkeys"), QStringList());

    for (QPair<QString, QStringList> pair : list) {
        startProcess(pair);
    }

    QTimer::singleShot(100, this, &ProcessManager::loadAutoStartProcesses);
    m_completedInit = true;
}

void ProcessManager::loadAutoStartProcesses()
{
    QStringList execList;
    QStringList xdgDesktopList;
    xdgDesktopList << "/etc/xdg/autostart";

    for (const QString &dirName : xdgDesktopList) {
        QDir dir(dirName);
        if (!dir.exists())
            continue;

        const QFileInfoList files = dir.entryInfoList(QStringList("*.desktop"), QDir::Files | QDir::Readable);
        for (const QFileInfo &fi : files) {
            QSettings desktop(fi.filePath(), QSettings::IniFormat);
            desktop.setIniCodec("UTF-8");
            desktop.beginGroup("Desktop Entry");

            if (desktop.contains("OnlyShowIn"))
                continue;

            const QString execValue = desktop.value("Exec").toString();

            if (!execValue.isEmpty()) {
                execList << execValue;
            }
        }
    }

    for (const QString &exec : execList) {
        QProcess *process = new QProcess;
        process->setProgram(exec);
        process->start();
        process->waitForStarted();

        qDebug() << "Load autostart: " << exec;

        if (process->exitCode() == 0) {
            m_autoStartProcess.insert(exec, process);
        } else {
            process->deleteLater();
        }
    }
}
