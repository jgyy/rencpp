import QtQuick 2.15

Rectangle {
    id: choiceButton

    width: parent.width
    height: 50
    color: mouseArea.containsMouse ? "#3d5a80" : "#2c4563"
    radius: 5
    border.color: "#1a2a3a"
    border.width: 2

    signal clicked

    Text {
        id: buttonText
        anchors.fill: parent
        anchors.margins: 10
        text: modelData.text
        color: "#ffffff"
        font.pixelSize: 14
        font.family: "Arial"
        wrapMode: Text.WordWrap
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            choiceButton.clicked()
        }

        onEntered: {
            choiceButton.scale = 1.02
        }

        onExited: {
            choiceButton.scale = 1.0
        }
    }

    Behavior on scale {
        NumberAnimation {
            duration: 200
        }
    }
}
