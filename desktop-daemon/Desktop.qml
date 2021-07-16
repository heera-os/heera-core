import QtQuick 2.4
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import Qt.labs.platform 1.0
import org.heera.Desktop 1.0
import HeeraUI 1.0 as HeeraUI

Item {
    visible: true
    id: root

    Settings {
        id: settings
    }

    Menu {
        id: menu

        MenuItem {
            text: qsTr("Change wallpaper")
            onTriggered: settings.launch("heera-settings", ["-m", "wallpaper"])
        }
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onClicked: menu.open()
    }

    Image {
        id: wallpaper
        anchors.fill: parent
        source: "file://" + settings.wallpaper
        sourceSize: Qt.size(width, height)
        fillMode: Image.PreserveAspectCrop
        clip: true
        cache: false

        ColorOverlay {
            id: dimsWallpaper
            anchors.fill: wallpaper
            source: wallpaper
            color: "#000000"
            opacity: 0.4
            visible: HeeraUI.Theme.darkMode && settings.dimsWallpaper
        }
    }
}
