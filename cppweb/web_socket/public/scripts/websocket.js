// ws:///ws
const url = location.origin.replace(/^http/, 'ws') + '/ws'
const socket = new WebSocket(url)
const id = Math.floor(Math.random() * 1000000)

createMessage = (id, type, body) => JSON.stringify({id, type, body})

socket.onopen = () => {
    console.log('open')
}

socket.onclose = () => {
    console.log('close')
}

socket.onerror = (e) => {
    console.log('error', e)
}

socket.onmessage = (e) => {
    console.log("message: " + e.data)
    const message = JSON.parse(e.data)
    switch(message.type) {
        case 'chat':
            $('#log').val(`${message.body}\n` + $('#log').val())
            break;
        default:
            console.log('Unknown message type')
    }
}

send_message = (event) => {
    console.log("Send message: " + $('#msg').val())
    socket.send(createMessage(id, 'chat', $('#msg').val()))
    $('#msg').val('')
}
