import Charts 1.0
import QtQuick 2.12
import QtQuick.Controls 1.4


Item {
    width: 300
    height: 200

    Row {
        PieChart {
            id: chartA
            width: 100
            height: 100
            color: "red"
            onColorChanged: console.log("ChartA color changed!")
        }

        PieChart {
            id: chartB
            width: 100
            height: 100
            color: chartA.color
            onColorChanged: console.log("ChartB color changed!")
        }

    }
    

    MouseArea {
        anchors.fill: parent
        onClicked: {
            chartA.color = "blue"
        }
    }

    Text {
        anchors {
            bottom: parent.bottom 
            horizontalCenter: parent.horizontalCenter
            bottomMargin: 20
        }

        text: "Click anywhere to change the chart color"
    }
}



