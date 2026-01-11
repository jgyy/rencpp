import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: mainWindow
    title: "Text Adventure"
    width: 900
    height: 700
    visible: true
    color: "#0f1a25"

    Component.onCompleted: {
        var xCenter = (Screen.width - width) / 2
        var yCenter = (Screen.height - height) / 2
        x = xCenter
        y = yCenter

        gameEngine.loadStory("qrc:/stories/sample_story.json")
    }

    GameScreen {
        anchors.fill: parent
    }
}
