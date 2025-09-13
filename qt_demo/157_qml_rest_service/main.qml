import QtQuick 2.12
import QtQuick.Controls 1.4
import "color_client.js" as Client 

ApplicationWindow {
    visible: true
    

    Rectangle {
        width: 480
        height: 320
        color: "#000"

        ListModel {
            id: gridModel
        }

        StatusLabel {
            id: message 
            anchors.bottom: parent.bottom 
            anchors.left: parent.left 
            anchors.right: parent.right 
        }

        GridView {
            id:view 
            anchors.top: parent.top 
            anchors.bottom: message.top 
            anchors.left: parent.left 
            anchors.right: sideBar.left 
            anchors.margins: 8
            model: gridModel 
            cellHeight: 64
            cellWidth: 64
            delegate: Rectangle {
                width: 64
                height: 64
                color: model.value 
            }     
        }

        Column {
            id: sideBar
            width: 160
            anchors.top: parent.top 
            anchors.bottom: parent.bottom 
            anchors.right: parent.right 
            anchors.margins: 8
            spacing: 8
            Button {
                text: "Read Colors"
                onClicked: {
                    Client.get_colors(function(resp) {
                        print("Handle get_colors response: "+ JSON.stringify(resp))
                        gridModel.clear()
                        var colors = resp.data
                        for(var i=0; i<colors.length; ++i) {
                            gridModel.append(colors[i])
                        }
                    })
                }
            }

            Button {
                text: "Create New"
                onClicked: {
                    var index = gridModel.count - 1
                    var color = {
                        name: "color-" + index,
                        value: Qt.hsla(Math.random(), 0.5, 0.5, 1.0).toString()
                    }
                    Client.create_color(color, function(resp) {
                        print("Hanle create_color response: " + JSON.stringify(resp))
                        gridModel.append(resp)
                    })
                }
            }

            Button {
                text: "Read Last Color"
                onClicked: {
                    var index = gridModel.count - 1
                    var name = gridModel.get(index).name 
                    Client.get_color(name, function(resp){
                        print("Handle get_color response: " + JSON.stringify(resp))
                        message.text = resp.value
                    })
                }
            } 

            Button {
                text: "Update Last Color"
                onClicked: {
                    var index = gridModel.count - 1
                    var name = gridModel.get(index).name 
                    var color = {
                        value: Qt.hsla(Math.random(),  0.5, 0.5, 1.0).toString()
                    } 
                    Client.update_color(name, color, function(resp){
                        print("Handle update_color response: " + JSON.stringify(resp))
                        var index = gridModel.count - 1
                        gridModel.setProperty(index, "value", resp.value)
                    })
                }
            }

            Button {
                text: "Delete Last Color"
                onClicked: {
                    var index = gridModel.count - 1
                    var name = gridModel.get(index).name 
                    Client.delete_color(name)
                    gridModel.remove(index, 1)
                }
            }  
        }

    }
    
}


