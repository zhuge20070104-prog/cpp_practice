import QtQuick 2.12
import QtQuick.LocalStorage 2.12


Item {
    property var db
    
    function initDatabase() {
        print("initDatabase()")
        db = LocalStorage.openDatabaseSync("Crazy Box", "1.0", "A box who remember its position", 100000)
        db.transaction(function(tx) {
            print("Create table...")
            tx.executeSql("CREATE TABLE IF NOT EXISTS data(name TEXT, value TEXT)")
        })
    }

    function storeData(crazy_x, crazy_y) {
        print("storeData()...")
        if(!db) return
        db.transaction(function(tx) {
            var result = tx.executeSql("SELECT * from data where name='crazy'")
            var obj = {x: crazy_x, y: crazy_y}
            // Use update
            if(result.rows.length === 1) {
                result = tx.executeSql("UPDATE data set value=? where name='crazy'", [JSON.stringify(obj)])
            } else {
                result = tx.executeSql("INSERT INTO data VALUES(?,?)", ["crazy", JSON.stringify(obj)])
            }
        })
    }

    function readData() {
        print("readData()")

        if(!db) return null
        var res = null
        db.transaction(function(tx) {
            var result = tx.executeSql("select * from data where name='crazy'");
            if(result.rows.length === 1) {
                var value = result.rows[0].value 
                res = JSON.parse(value)
            }
        })
        return res
    }

    
}
