import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import Qt.labs.settings 1.0


Window {
    id: root
    visible: true
    width: 400
    height: 400
    title: qsTr("Sqlite Storage Demo")
    
    Rectangle {
        id: crazy
        objectName: "crazy"
        width: 100
        height: 100
        x: 50
        y: 50
        color: "#53d769"
        border.color:  Qt.lighter(color, 1.1)

        Text {
            anchors.centerIn: parent 
            text: Math.round(parent.x) + '/' + Math.round(parent.y) 
        }

        MouseArea {
            anchors.fill: parent 
            drag.target: parent 
        }
    }

    DB {
        id: db
    }

    Component.onCompleted: {
        db.initDatabase()
        var pos = db.readData()
        if(pos != null) {
            crazy.x = pos.x
            crazy.y = pos.y
        }
    }
    Component.onDestruction: {
        db.storeData(crazy.x, crazy.y)
    }
}
