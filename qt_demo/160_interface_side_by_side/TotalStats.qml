import QtQuick 2.12
import QtQuick.Controls 2.4

Page {
    header: Label {
        text: qsTr("Community Stats")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Column {
        anchors.centerIn: parent 
        spacing: 10

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Community Statistics") 
        } 

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Back")
            onClicked: swipeView.setCurrentIndex(0) 
        }
    }
}