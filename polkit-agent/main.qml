import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import HeeraUI 1.0 as HeeraUI

Rectangle {
    id: root
    width: 550
    height: mainLayout.implicitHeight + 50

    radius: HeeraUI.Units.largeRadius
    color: HeeraUI.Theme.primaryBackgroundColor
    border.color: Qt.rgba(0, 0, 0, 0.4)
    border.width: 1

    HeeraUI.WindowShadow {
        view: rootWindow
        geometry: Qt.rect(root.x, root.y, root.width, root.height)
        radius: root.radius
    }

    RowLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: parent.radius * 2

        Image {
            id: icon
            source: "qrc:/svg/emblem-warning.svg"
            sourceSize.width: 96
            sourceSize.height: 96
            smooth: true
            Layout.alignment: Qt.AlignTop
        }

        Item {
            width: 10
        }

        ColumnLayout {
            Label {
                text: confirmation.message
                wrapMode: Text.WordWrap
                font.bold: true
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Item {
                height: 5
            }

            TextField {
                id: userTextField
                text: confirmation.identity
                enabled: false
                Layout.fillWidth: true
            }

            TextField {
                id: passwordInput
                placeholderText: qsTr("Password")
                echoMode: TextField.Password
                Layout.fillWidth: true
                selectByMouse: true
                focus: true
                onAccepted: {
                    if (passwordInput.text)
                        confirmation.setConfirmationResult(passwordInput.text)
                }
            }

            Item {
                height: 5
            }

            RowLayout {
                Button {
                    id: doneButton
                    text: qsTr("Done")
                    Layout.fillWidth: true
                    height: 50
                    onClicked: confirmation.setConfirmationResult(passwordInput.text)
                }

                Button {
                    text: qsTr("Cancel")
                    Layout.fillWidth: true
                    height: 50
                    onClicked: confirmation.setConfirmationResult("")
                }
            }
        }
    }
}
