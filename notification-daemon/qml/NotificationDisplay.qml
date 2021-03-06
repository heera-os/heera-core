import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import org.heera.NotificationDaemon 1.0
import HeeraUI 1.0 as HeeraUI
import QtGraphicalEffects 1.15

NotificationBase {
	id: root
	width: 500
	height: _layout.implicitHeight + HeeraUI.Units.largeSpacing * 4
	visible: true

	property point position: Qt.point(Screen.width, Screen.height)
	required property Notification notification

	signal closed()
	
	color: "transparent"

	function adjustCorrectLocation() {
		var posX = root.position.x
		var posY = root.position.y

		// left
		if (posX < 0)
			posX = HeeraUI.Units.largeSpacing
		
		// top
		if (posY < 0)
			posY = HeeraUI.Units.largeSpacing
		
		// right
		if (posX + root.width > Screen.width)
			posX = Screen.width - root.width - HeeraUI.Units.largeSpacing - 2

		// bottom
		if (posY + root.height > Screen.height)
			posY = Screen.height - root.height - HeeraUI.Units.largeSpacing

		root.x = posX
		root.y = posY
	}

	HeeraUI.RoundedRect {
		id: _background
		anchors.fill: parent
		radius: HeeraUI.Units.largeRadius
		color: HeeraUI.Theme.primaryBackgroundColor
		opacity: 0.5
	}

	HeeraUI.WindowShadow {
		view: root
		geometry: Qt.rect(root.x, root.y, root.width, root.height)
		radius: _background.radius
	}

	ColumnLayout {
		anchors.margins: HeeraUI.Units.largeSpacing * 2
		anchors.fill: parent
		spacing: HeeraUI.Units.largeSpacing
		id: _layout

		RowLayout {
			Layout.fillWidth: true
			height: 64

			Image {
				id: _notifAppIcon
				source: notification.iconPath
				width: 64
				height: 64
				sourceSize: Qt.size(64, 64)
			}

			ColumnLayout {
				Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
				Layout.fillWidth: true

				Label {
					Layout.fillWidth: true
					text: notification.appTitle
					elide: Text.ElideRight
					clip: true
				}

				Label {
					Layout.fillWidth: true
					text: notification.summary
					elide: Text.ElideRight
					font.pointSize: 12
					clip: true
				}
			}

			Item {
				Layout.fillWidth: true
			}

			Image {
				Layout.alignment: Qt.AlignRight | Qt.AlignTop
				source: "qrc:/images/" + (HeeraUI.Theme.darkMode ? "light" : "dark") + "/close.svg"
				
				MouseArea {
					id: mouseArea
					anchors.fill: parent
					acceptedButtons: Qt.LeftButton
					hoverEnabled: true

					onClicked: root.closed()

					Rectangle {
						id: highlight
						color: HeeraUI.Theme.textColor
						opacity: mouseArea.pressed ? 0.3 :
							mouseArea.containsMouse ? 0.1 : 0
						anchors.fill: parent
						radius: highlight.width / 2

						Behavior on opacity {
							NumberAnimation {
								duration: 125
								easing.type: Easing.InOutCubic
							}
						}
					}
				}
			}
		}

		Label {
			Layout.fillWidth: true

			text: notification.body
			elide: Text.ElideRight
			clip: true
		}
	}
}
