import QtQuick 2.12
import QtQuick.Controls 1.4


ApplicationWindow {
    visible: true
    

    Canvas {
        id: root 
        width: 200
        height: 200
        onPaint: {
            var ctx = getContext("2d")

            ctx.strokeStyle = "red"
            ctx.beginPath()
            ctx.moveTo(50, 50)
            ctx.lineTo(150, 50)
            ctx.stroke()
        }
    }
}


