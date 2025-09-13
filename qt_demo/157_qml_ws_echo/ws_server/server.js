var WebSocketServer = require("ws").Server 

var server = new WebSocketServer({port: 3000})
var sockets = []
server.on("connection", function(socket){
    console.log("Client connected")
    sockets.push(socket)
    socket.on("message", function(msg) {
        server.clients.forEach((sock)=>{
            sock.send("" + msg)
        })
    })
    socket.send("Welcome to Awesome Chat")
})

console.log("listening on port " + server.options.port)