import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 500
    height: 500
    color: "white"


    Slider {
        id: slide 
        width: parent.width
        minimumValue: 0
        maximumValue: 360
        value: 0
        enabled: true 
        onValueChanged: {
            // Need to put all the sub rectangles into the parent to enable
            // rotation for all of the children
            recCenter.rotation = slide.value
        }
    }

    Rectangle {
        id: recCenter
        width: parent.width/ 2
        height: parent.height/ 2
        color: "green"
        anchors.centerIn: parent 
        GreenBox {
            id: recTopLeft
            anchors.right: recCenter.left
            anchors.bottom: recCenter.top
        }

        GreenBox {
            id: recLeft
            anchors.right: recCenter.left
            anchors.verticalCenter: recCenter.verticalCenter
        }

        GreenBox {
            id: recLeftBottom
            anchors.right: recCenter.left
            anchors.top: recCenter.bottom
        }

        GreenBox {
            id: recTopCenter
            anchors.horizontalCenter: recCenter.horizontalCenter
            anchors.bottom: recCenter.top
        }

        GreenBox {
            id: recTopRight
            anchors.left: recCenter.right
            anchors.bottom: recCenter.top
        }

        GreenBox {
            id: recRight
            anchors.left: recCenter.right
            anchors.verticalCenter: recCenter.verticalCenter
        }

        GreenBox {
            id: recBottomRight
            anchors.left: recCenter.right
            anchors.top: recCenter.bottom
        }

        GreenBox {
            id: recBottomCenter
            anchors.horizontalCenter: recCenter.horizontalCenter
            anchors.top: recCenter.bottom
        }
    }
}
