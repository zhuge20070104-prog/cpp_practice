import Charts 1.0
import QtQuick 2.12
import QtQuick.Controls 1.4


Item {
    width: 300
    height: 200

    PieChart {
        id: chart
        anchors.centerIn: parent
        width: 100
        height: 100
        name: "Pie chart with slices"
        slices: [
            Pieslice {
                anchors.fill: parent 
                color: "red"
                fromAngle: 0
                angleSpan: 110
            },
            Pieslice {
                anchors.fill: parent 
                color: "black"
                fromAngle: 110
                angleSpan:  50
            },
            Pieslice {
                anchors.fill: parent 
                color: "blue"
                fromAngle: 160
                angleSpan:  100
            }
        ]
    }
}



