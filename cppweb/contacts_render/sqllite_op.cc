#include "sqllite_op.h"
#include <iostream>

SQLiteOp::SQLiteOp(std::string const& db_name_): db_name(db_name_) {}

void SQLiteOp::Open() {
    char *zErrMsg = 0;
    int rc;
    char *sql;

    /* Open database */
    rc = sqlite3_open(db_name.data(), &db);
    if( rc ){
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << "\n"; 
        exit(0);
    }else{
        is_closed = false;
        std::cout << "Opened database successfully\n";
    }
}

void SQLiteOp::Close() {
    std::cout << "Close DB\n";
    sqlite3_close(db);
    is_closed = true;
}

bool SQLiteOp::ExecUpdate(std::string const& updateSql) {
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, updateSql.data(), nullptr, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        std::cerr << "SQL error: " << zErrMsg << "\n";
        sqlite3_free(zErrMsg);
        return false;
    }else{
        std::cout << "Records created successfully\n";
        return true;
    }
}

ResultMap SQLiteOp::Query(std::string const& querySql) {
    ResultMap results;
    char *zErrMsg = 0;
    /* Execute SQL statement */
    int rc = sqlite3_exec(db, querySql.data(), [](void *data, int argc, char **argv, char **azColName) {
            int i;
            auto& results_ = *((ResultMap*)(data));
            std::map<std::string, std::string> result;
            for(i=0; i<argc; i++){
                if(argv[i]) {
                    result[azColName[i]] =  argv[i];
                } else {
                    result[azColName[i]] = "NULL";
                }
            }
            results_.emplace_back(std::move(result));
            return 0;
    }, (void*)&results, &zErrMsg);

    if( rc != SQLITE_OK ){
        std::cerr << "SQL error: " << zErrMsg << "\n";
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "Operation done successfully\n";
    }
    return results;
}

SQLiteOp::~SQLiteOp() {
    if(!is_closed) {
        std::cout << "Close DB\n";
        sqlite3_close(db);
    }
}