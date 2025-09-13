import QtQuick 2.12
import QtQuick.Controls 1.4


ApplicationWindow {
    visible: true
    

    Canvas {
        id: canvas
        width: 400
        height: 200
        smooth: true
        onPaint: {
            var ctx = getContext("2d")
            ctx.strokeStyle = "#333"
            ctx.fillRect(0, 0, canvas.width, canvas.height)

            // Setup a blue shadow
            ctx.shadowColor = "#2ed5fa"
            ctx.shadowOffsetX = 2
            ctx.shadowOffsetY = 2
            ctx.shadowBlur = 10

            // Render green text 
            ctx.font = "bold 80px Ubuntu"
            ctx.fillStyle = "#24d12e"
            ctx.fillText("Canvas!", 30, 180)        

        }
    }
}


