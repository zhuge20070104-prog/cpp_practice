.pragma library

var BASE = "http://localhost:5000/colors"

function get_colors(cb) {
    request("GET", null, null, cb)
}

function create_color(color, cb) {
    request("POST", null, color, cb)
}

function get_color(name, cb) {
    request("GET", name, null, cb)
}

function update_color(name, color, cb) {
    request("PUT", name, color, cb)
}

function delete_color(name, cb) {
    request("DELETE", name, null, cb)
}

function request(method, endpoint, data, cb) {
    var url = BASE + (endpoint? "/" + endpoint: "")
    print("Request method: " + method)
    print("Request url: " + url)
    var xhr = new XMLHttpRequest()
    xhr.onreadystatechange = function() {
        print("xhr.onreadystatechange: " + xhr.readyState)
        if(xhr.readyState === XMLHttpRequest.DONE) {
            if(cb) {
                var text = xhr.responseText.toString()
                print(text)
                var res = JSON.parse(text)
                cb(res)
            }
        }
    }

    xhr.open(method, url)
    xhr.setRequestHeader("Content-Type", "application/json")
    xhr.setRequestHeader("Accept", "application/json")
    var send_data = data? JSON.stringify(data): ""
    xhr.send(send_data)
}