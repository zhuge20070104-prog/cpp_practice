import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4

Window {
    id: root
    visible: true
    width: 500
    height: 500

    Column {
        id: cols 
        anchors.fill: parent 
        anchors.margins: 5
        spacing: 3

        Rectangle {
            id: frame 
            width: parent.width
            height: 25
            border.color: "gray"
            border.width: 1
            TextInput {
                id: txtPlain
                anchors.fill: parent 
                anchors.margins: 4
                onTextChanged:  {
                    txtEncoded.text = Qt.btoa(txtPlain.text)
                }  
            } 
        }  

        Rectangle {
            id: frame2
            width: parent.width 
            height: parent.height - (frame.height+cols.spacing)
            TextArea {
                id: txtEncoded
                anchors.fill: parent 
            }
        }
    }
    
}
