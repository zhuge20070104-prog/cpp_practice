import QtQuick 2.12

Item {
    
    function request(url, view) {
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if(xhr.readyState ===  XMLHttpRequest.HEADERS_RECEIVED) {
                print("HEADERS_RECEIVED")
            } else if(xhr.readyState === XMLHttpRequest.DONE) {
                print("DONE")
                var text = xhr.responseText.toString()
                print(text)
                var json = JSON.parse(text)
                view.model = json.result.data
            }
        }

        xhr.open("GET", url)
        xhr.send()
    }
}