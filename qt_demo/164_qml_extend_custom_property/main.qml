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
        name: "A simple pie chart"
        pieSlice: Pieslice {
            anchors.fill: parent
            color: "red"
        }
    }

   Component.onCompleted: console.log("The pie is colored: " + chart.pieSlice.color)
}



