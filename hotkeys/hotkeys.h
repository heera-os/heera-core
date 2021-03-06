

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

#ifndef HOTKEYS_H
#define HOTKEYS_H

#include <QObject>
#include <QKeySequence>
#include <QList>
#include <QDebug>
#include <QProcess>
#include <QHotkey>

class Hotkeys : public QObject {
	Q_OBJECT

public:
	Hotkeys(QObject *parent = nullptr);

public slots:
	void startLauncher();
	void startTerminal();
};

#endif // HOTKEYS_H
