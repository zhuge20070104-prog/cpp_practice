import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Controls.Material 2.12


ApplicationWindow {
    visible: true
    

    Rectangle {
        width: 320
        height: 320

        Text {
            id: label
            anchors.top: parent.top 
            anchors.left: parent.left 
            anchors.right: parent.right
            anchors.margins: 15
            horizontalAlignment: Text.AlignHCenter
            text: "Checkbox presents an option button that can be toggled on or off.Checkbox are typically used to select one or more options from a set of options"
            wrapMode: Text.WordWrap
        }


        Column {
            
            width: parent.width

            anchors.left: parent.left 
            anchors.top: label.bottom 
            anchors.topMargin: 30 
            anchors.leftMargin: 50
            spacing: 10
            CheckBox {
                text: qsTr("First")
                checked: true
            }  
            CheckBox {
                text: qsTr("Second")
            }  
            CheckBox {
                text: qsTr("Third")
                checked: true 
                enabled: false
            }
        }
    }
}


