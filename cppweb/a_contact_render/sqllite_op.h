#ifndef _FREDRIC_SQLITE_OP_H_
#define _FREDRIC_SQLITE_OP_H_

#include <string>
#include <map>
#include <vector>
#include "sqlite3.h"

using ResultMap = std::vector<std::map<std::string, std::string>>;

struct SQLiteOp {
public:
    SQLiteOp(std::string const& db_name_);
    ~SQLiteOp();
    void Open();
    void Close();
    bool ExecUpdate(std::string const& updateSql);
    ResultMap Query(std::string const& querySql);
private:
    std::string db_name;
    sqlite3 *db;
    bool is_closed {true};
};

#endif