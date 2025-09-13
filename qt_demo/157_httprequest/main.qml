import QtQuick 2.12
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true
    Rectangle {
        width: 480
        height: 800

        ListView {
            id: view 
            anchors.fill: parent 
            delegate: Thumbnail {
                width: view.width 
                text: modelData.title 
                iconSource: modelData.thumbnail_pic_s
            }
        }
    }

    Request {
        id: req 
    }

    Component.onCompleted: {
        req.request("http://v.juhe.cn/toutiao/index?type=top&key=3dc86b09a2ee2477a5baa80ee70fcdf5", view)
    }
}


