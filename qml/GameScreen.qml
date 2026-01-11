import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: gameScreen
    color: "#0f1a25"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        // Title
        Text {
            text: "The Mysterious Room"
            color: "#ffffff"
            font.pixelSize: 28
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
            font.family: "Georgia"
        }

        // Story display area
        StoryView {
            id: storyView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 300
        }

        // Choices area
        Rectangle {
            color: transparent
            Layout.fillWidth: true
            Layout.preferredHeight: choicesColumn.implicitHeight + 10

            ColumnLayout {
                id: choicesColumn
                anchors.fill: parent
                spacing: 8

                Repeater {
                    model: gameEngine.choices

                    delegate: ChoiceButton {
                        Layout.fillWidth: true
                        onClicked: {
                            gameEngine.makeChoice(index)
                        }
                    }
                }
            }
        }

        // Control buttons
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Button {
                text: "Back"
                enabled: gameEngine.canGoBack
                onClicked: {
                    gameEngine.goBack()
                }
                background: Rectangle {
                    color: parent.enabled ? "#3d5a80" : "#1a2a3a"
                    border.color: "#1a2a3a"
                    border.width: 1
                    radius: 3
                }
                contentItem: Text {
                    text: parent.text
                    color: parent.enabled ? "#ffffff" : "#666666"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 12
                }
            }

            Button {
                text: "Restart"
                onClicked: {
                    gameEngine.restart()
                }
                background: Rectangle {
                    color: "#3d5a80"
                    border.color: "#1a2a3a"
                    border.width: 1
                    radius: 3
                }
                contentItem: Text {
                    text: parent.text
                    color: "#ffffff"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 12
                }
            }

            Item {
                Layout.fillWidth: true
            }
        }

        // Status message for endings
        Text {
            id: endingMessage
            visible: gameEngine.isGameEnded
            color: "#90EE90"
            font.pixelSize: 14
            font.bold: true
            text: "This story has ended. Click Restart to play again."
            Layout.alignment: Qt.AlignHCenter
        }
    }

    // Handle errors
    Connections {
        target: gameEngine
        function onErrorOccurred(error) {
            errorDialog.errorMessage = error
            errorDialog.open()
        }
    }

    // Error dialog
    Dialog {
        id: errorDialog
        property string errorMessage: ""
        title: "Error"
        anchors.centerIn: parent
        modal: true

        contentItem: Text {
            text: errorDialog.errorMessage
            color: "#ffffff"
            wrapMode: Text.WordWrap
        }

        background: Rectangle {
            color: "#1a2a3a"
            border.color: "#ff6b6b"
            border.width: 2
            radius: 5
        }

        Button {
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 10
            text: "OK"
            onClicked: errorDialog.close()

            background: Rectangle {
                color: "#3d5a80"
                border.color: "#1a2a3a"
                radius: 3
            }

            contentItem: Text {
                text: parent.text
                color: "#ffffff"
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }
}
