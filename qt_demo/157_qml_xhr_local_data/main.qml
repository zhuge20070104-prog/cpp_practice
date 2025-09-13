import QtQuick 2.12
import QtQuick.Controls 1.4
import "req.js" as Req

ApplicationWindow {
    visible: true
    

    Rectangle {
        width: 360
        height: 360
        color: "#000"

        GridView {
            id: view 
            anchors.fill: parent 
            cellWidth: width /4 
            cellHeight: cellWidth 
            delegate: Rectangle {
                width: view.cellWidth
                height: view.cellHeight 
                color: modelData.value
            } 
        }
        Component.onCompleted: {
            Req.request("colors.json", function(data) {
                view.model = data.colors
            })
        }
    }
    
}


