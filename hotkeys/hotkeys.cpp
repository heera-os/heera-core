
/*
 * Copyright (C) 2020 HeeraOS Project
 *
 * Author:     omame <me@omame.tech>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "hotkeys.h"
#include <QKeySequence>
void startProcess(QPair<QString, QStringList> pair) {
    QProcess *process = new QProcess;
    process->setProcessChannelMode(QProcess::ForwardedChannels);
    process->setProgram(pair.first);
    process->setArguments(pair.second);
    process->start();
    process->waitForStarted();
}

Hotkeys::Hotkeys(QObject *parent) : QObject(parent) {
	// register shortcut
	auto launcherShortcut = new QHotkey();
	auto nativeShortcut = QHotkey::NativeShortcut(133);
	qDebug() << nativeShortcut.isValid();
	launcherShortcut->setNativeShortcut(nativeShortcut, true);
	qDebug() << "Launcher hotkey registered:" << launcherShortcut->isRegistered();
	
	auto terminalShortcut = new QHotkey();
	terminalShortcut->setShortcut(QKeySequence("Ctrl+Alt+t"), true);
	qDebug() << "Terminal hotkey registered:" << terminalShortcut->isRegistered();
	
	connect(terminalShortcut, &QHotkey::activated, this, &Hotkeys::startTerminal);
	connect(launcherShortcut, &QHotkey::activated, this, &Hotkeys::startLauncher);
}

void Hotkeys::startLauncher() {
	qDebug() << "Starting launcher...";
    startProcess(qMakePair(QString("heera-launcher"), QStringList()));
}

void Hotkeys::startTerminal() {
	qDebug() << "Starting terminal...";
    startProcess(qMakePair(QString("heera-terminal"), QStringList()));
}
