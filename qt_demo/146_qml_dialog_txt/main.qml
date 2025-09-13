import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.3

Window {
    id: root
    visible: true
    width: 500
    height: 500

    ColorDialog {
        id: colorDialog
        modality: Qt.WindowModal
        title: "Choose a color"
        color: "green"
        onAccepted: {
            console.log("Accepted: " + color)
        }
        onRejected: {
            console.log("Rejected!")
        }
    }

    FontDialog {
        id: fontDialog 
        modality: Qt.WindowModal
        title: "Choose a font"
        onAccepted: {
            console.log("Accepted: " + font)
        }
        onRejected: {
            console.log("Rejected!")
        }
    }

    Row {
        Button {
            id: btnColor
            text: "Color"
            onClicked: {
                colorDialog.open()
            }
        }

        Button {
            id: btnFont
            text: "Font"
            onClicked: {
                fontDialog.open()
            }
        }

        TextField {
            id: txtText 
            text: "Enter some text"
            width: 300
        }
    }

    Text {
        id: preview 
        anchors.centerIn: parent 
        font: fontDialog.font 
        color: colorDialog.color 
        text: txtText.text 
    }
    
}
