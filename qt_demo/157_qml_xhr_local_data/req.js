.pragma library

function request(url, cb) {
    var xhr = new XMLHttpRequest()
    xhr.onreadystatechange = function() {
        if(xhr.readyState === XMLHttpRequest.HEADERS_RECEIVED) {
            print("HEADERS_RECEIVED")
        } else if(xhr.readyState === XMLHttpRequest.DONE) {
            print("DONE")
            var text = xhr.responseText.toString()
            print(text)
            if(cb) {
                var obj = JSON.parse(text)
                cb(obj)
            }
        }
    }

    xhr.open("GET", url)
    xhr.send()
}