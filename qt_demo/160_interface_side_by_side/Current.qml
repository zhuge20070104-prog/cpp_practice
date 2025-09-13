import QtQuick 2.12
import QtQuick.Controls 2.4

Page {
    header: Label {
        text: qsTr("Current")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Label {
        text: qsTr("Current Activity")
        anchors.centerIn: parent  
    }
}