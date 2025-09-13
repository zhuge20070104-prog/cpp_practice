#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include "sqllite_op.h"


void createDBStructure(SQLiteOp& sqlite_op) {
   /* Create SQL statement */
    std::string createTabelSql = "CREATE TABLE COMPANY("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NAME           TEXT    NOT NULL," \
         "AGE            INT     NOT NULL," \
         "ADDRESS        CHAR(50)," \
         "SALARY         REAL );";
    sqlite_op.ExecUpdate(createTabelSql);
    
    /* Create SQL statement */
    std::string insertDataSql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";
    sqlite_op.ExecUpdate(insertDataSql);
}

int main(int argc, char* argv[]) {
    std::string db_name {"./test.db"};
    bool shouldCreateDB {false};
    if(!boost::filesystem::exists(db_name)) {
        shouldCreateDB = true;
    }

    SQLiteOp sqlite_op {db_name};
    sqlite_op.Open();
    std::string querySql = "SELECT * from COMPANY";
    std::cout << "DB Name: " << db_name << std::endl;

    if(shouldCreateDB) {
        std::cout << "db not exists\n";
        createDBStructure(sqlite_op);
    }

    auto results = sqlite_op.Query(querySql);
    for(auto const& result: results) {
        for(auto const& entry: result) {
            std::cout << entry.first << ": " << entry.second << "\t";
        }
        std::cout << "\n";
    }

    sqlite_op.Close();
    sqlite_op.Open();

    results = sqlite_op.Query(querySql);
    for(auto const& result: results) {
        for(auto const& entry: result) {
             std::cout << entry.first << ": " << entry.second << "\t";
        }
        std::cout << "\n";
    }
    return 0;
}