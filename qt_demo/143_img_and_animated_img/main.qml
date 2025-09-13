import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 1100
    height: 640
    color: "white"

    Slider {
        id: slider
        width: parent.width
        minimumValue: 0
        maximumValue: 360
        value: 0

        onValueChanged: {
            console.log(value)
            banana.rotation = value
        }
    }

    Image {
        anchors.top: slider.bottom 
        id: background
        fillMode: Image.PreserveAspectFit
        source: "images/tom.jpg"
    }   

    AnimatedImage {
        id: banana
        source: "images/banana.gif"
        anchors.centerIn: background
        opacity: 0.5 
    }
}
