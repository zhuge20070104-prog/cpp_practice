import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.3

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Traffic Light")

    Column {
        spacing: 15
        anchors.centerIn: parent 

        Button {
            id: btnStop 
            text: "Stop"
            onClicked: myStopLight.state = "stop"
        }  

        Button {
            id: btnGo 
            text: "Go"
            onClicked: myStopLight.state = "go"
        }  

        StopLight {
            id: myStopLight
            state: "stop"
        }
    }


 
}
