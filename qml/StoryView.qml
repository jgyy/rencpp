import QtQuick 2.15

Rectangle {
    id: storyView

    color: "#1a2a3a"
    border.color: "#3d5a80"
    border.width: 2
    radius: 5

    ScrollView {
        id: scrollView
        anchors.fill: parent
        anchors.margins: 10
        contentWidth: storyText.width

        Text {
            id: storyText
            width: storyView.width - 20
            text: gameEngine.currentText
            color: "#e8e8e8"
            font.pixelSize: 16
            font.family: "Georgia"
            wrapMode: Text.WordWrap
            lineHeight: 1.6
            lineHeightMode: Text.ProportionalHeight
            padding: 10

            Behavior on text {
                SequentialAnimation {
                    NumberAnimation {
                        target: storyText
                        property: "opacity"
                        to: 0
                        duration: 150
                    }
                    PropertyAction {
                        target: storyText
                        property: "text"
                    }
                    NumberAnimation {
                        target: storyText
                        property: "opacity"
                        to: 1
                        duration: 150
                    }
                }
            }
        }
    }
}
