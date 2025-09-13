import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.3

Window {
    id: root
    visible: true
    width: 500
    height: 500

    Row {
        id: tools 
        Button {
            id: clear 
            text: "Clear"
            onClicked: {
                mouses.clear()
                var ctx = canvas.getContext("2d")
                ctx.reset()
                canvas.requestPaint()
            }
        }

        Button {
            id: save 
            text: "Save"
            onClicked:  {
                mouses.save()
            }
        }
    }

    Canvas {
        id: canvas 
        anchors.top: tools.bottom 
        width: 500
        height: 500

        property int lastX: 0
        property int lastY: 0
        property bool first_run: true

        onPaint: {
            
            var ctx = getContext("2d")
            ctx.lineWidth = 2
            ctx.strokeStyle = "#ff0000"
            ctx.beginPath()
            
            if(canvas.first_run == true) {
                for(var i=0; i<mouses.points.length; ++i) {
                    ctx.moveTo(mouses.points[i].x, mouses.points[i].y)
                    if(i+1 < mouses.points.length) {
                         ctx.lineTo(mouses.points[i+1].x, mouses.points[i+1].y)
                    }
                   
                }
                if(mouses.points.length > 0) {
                    var last_idx = mouses.points.length-1
                    ctx.moveTo(mouses.points[last_idx].x, mouses.points[last_idx].y)
                    ctx.lineTo(mouses.points[0].x, mouses.points[0].y)
                }
                canvas.first_run = false
                
            }  else {
                ctx.moveTo(lastX, lastY)
                lastX = area.mouseX 
                lastY = area.mouseY 
                ctx.lineTo(lastX, lastY)
            }
            ctx.stroke()
        } 

        MouseArea {
            id: area
            anchors.fill: parent 
            onPressed:  {
                canvas.lastX = mouseX 
                canvas.lastY = mouseY
                mouses.add(mouseX, mouseY)
            } 
            onPositionChanged: {
                canvas.requestPaint()
            }
        }
    }

    Component.onCompleted: {
        canvas.requestPaint()
    }
}
