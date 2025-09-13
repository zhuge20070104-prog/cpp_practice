#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include <sstream>
#include "sqllite_op.h"
#include "b64_encoder.h"
#include "json.hpp"
#include "data.h"

using ordered_json = nlohmann::basic_json<nlohmann::ordered_map>;

void createDBStructure(SQLiteOp& sqlite_op) {
   /* Create SQL statement */
    std::string createContentTableSql = R"(
        CREATE TABLE case_content(
            content TEXT NOT NULL
        )
    )";
    sqlite_op.ExecUpdate(createContentTableSql);

    // Insert the raw data for testing
    auto encodedResult = Base64::encode64(json_content);
    std::stringstream insertSqlSS;
    insertSqlSS << "insert into case_content(content) values('" <<encodedResult << "')";
    sqlite_op.ExecUpdate(insertSqlSS.str());
}


int main(int argc, char* argv[]) {
    std::string db_name {"./test.db"};
    bool shouldCreateDB {false};
    if(!boost::filesystem::exists(db_name)) {
        shouldCreateDB = true;
    }

    SQLiteOp sqlite_op {db_name};
    sqlite_op.Open();

    if(shouldCreateDB) {
        createDBStructure(sqlite_op);
    }

    std::stringstream querySqlSS;
    querySqlSS<< "select content from case_content limit 1";
    auto queryRes = sqlite_op.Query(querySqlSS.str());
    auto encodedFromDB = queryRes[0]["content"];
    auto decodedStr = Base64::decode64(encodedFromDB);
    std::cout << "Decoded data: \n";
    std::cout << decodedStr << "\n";

    std::cout << "Get fields: \n";
    ordered_json js = ordered_json::parse(decodedStr);
    std::cout << "Failed cases: " << js["failed_cases"].get<int>() << "\n";
    std::cout << "c1 中文: " << js["c1"].get<std::string>() << "\n";
    
    return EXIT_SUCCESS;
}