import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.12


Window {
    id: root 
    signal valueChanged(string value)
    property alias currentIndex: input.currentIndex
    title: "Value Dialog"
    width: 300
    height: 90
    // flags: Qt.Popup
    modality: Qt.ApplicationModal
    x: Screen.width/2-width/2
    y: Screen.height/2-height/2
    Column{ 
        anchors.fill: parent 
        Rectangle {
            width: parent.width
            height: 30
            color: "silver"
            Text{
                width: contentWidth
                height: parent.height
                text: "请选择dx的值:"
            }
        }

        Rectangle {
            height: 30
            width: parent.width
            border.width: 2
            border.color: "gray"
            ComboBox {
                id: input
                width: parent.width
                height: parent.height
                model: ["0", "1"]
            }
        }

        Row {
            width: parent.width
            height: 30
            Rectangle {
              
                border.width: 1
                border.color: "gray"
                width: parent.width /2
                height: 30
                color: "silver"

                Button {
                    id: ok 
                    width: parent.width -4
                    height: parent.height 
                    anchors.centerIn: parent
                    text: "确定"
                    onClicked: {
                        root.hide()
                        root.valueChanged(input.currentText)
                    }

                    Keys.onReturnPressed: {
                        root.hide();
                    }
                }
            }

             Rectangle {
                border.width: 1
                border.color: "gray"
                width: parent.width /2
                height: 30
                color: "silver"

                Button {
                    id: cancel 
                    width: parent.width -4
                    height: parent.height 
                    anchors.centerIn: parent
                    text: "取消"
                    onClicked: {
                        root.hide()
                    }

                    Keys.onReturnPressed: {
                        root.hide();
                    }
                }
            }
        }

    
    }
}