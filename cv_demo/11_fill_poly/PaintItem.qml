import QtQuick 2.12
import QtQuick.Controls 2.4
import cvimages 1.0



Column {
    property alias text: label.text
    property alias image: img
    Label {
        id:label
        text: "Simple"
        anchors.horizontalCenter: parent.horizontalCenter
    }
    
    Rectangle {
        width: parent.width
        height: 5
    }
    Rectangle {
        border.width: 2
        border.color: "gray"
        id: content
        width: 500
        height: 500
      
        CVImageItem
        {   
            anchors.fill: parent
            id: img
        }
    }
}
