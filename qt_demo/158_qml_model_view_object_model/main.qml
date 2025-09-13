import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQml.Models 2.12

ApplicationWindow {
    visible: true
    Rectangle {
        width: 320
        height: 320

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#f6f6f6" }
            GradientStop { position: 1.0; color: "#d7d7d7" }
        }

        ObjectModel {
            id: itemModel 
            Rectangle { width: 80; height: 60; color: "#157efb"}
            Rectangle { width: 300; height: 20; color: "#53d769" 
                Text {
                    anchors.centerIn: parent 
                    color: "black"
                    text: "Hello QML" 
                }}
            
            Rectangle {
                width: 40; height: 40; radius: 10; color: "#fc1a1c"
            }
        }

        ListView {
            anchors.fill: parent 
            anchors.margins: 10
            spacing: 5
            model: itemModel  
        }
    }
}


