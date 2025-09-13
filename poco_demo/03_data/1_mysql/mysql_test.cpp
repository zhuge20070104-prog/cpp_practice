#include "gtest/gtest.h"
#include "Poco/Data/MySQL/MySQL.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/StatementImpl.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/Utility.h"
#include "Poco/Data/MySQL/MySQLException.h"
#include "Poco/Nullable.h"
#include "Poco/Data/DataException.h"
#include "Poco/SharedPtr.h"
#include "Poco/Tuple.h"

using namespace Poco::Data;
using namespace Poco::Data::Keywords;
using Poco::Tuple;
using Poco::Data::Session;
using Poco::Data::MySQL::Utility;
using Poco::Data::MySQL::ConnectionException;
using Poco::Data::MySQL::StatementException;


int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

class MySQLTestSuites: public testing::Test {
protected: 
    static void dbInfo(Session& session) {
        std::cout << "Server Info: " << Utility::serverInfo(session) << std::endl;
        std::cout << "Server Version: " << Utility::serverVersion(session) << std::endl;
        std::cout << "Host Info: " << Utility::hostInfo(session) << std::endl;
    }

    static void connectNoDB() {
        std::string dbConnString = "host=127.0.0.1"
		";user=root"
		";password=root"
		";compress=true;auto-reconnect=true;protocol=tcp";

        try {
            Session session(MySQL::Connector::KEY, dbConnString);
            std::cout << "Connected to [" << "MySQL" << "] without database." << std::endl;
            dbInfo(session);
            session << "CREATE DATABASE IF NOT EXISTS stu_db;", now;
            std::cout << "Disconnecting ..." << std::endl;
            session.close();
            std::cout << "Disconnected." << std::endl;
        }
        catch (ConnectionFailedException& ex)
        {
            std::cout << ex.displayText() << std::endl;
        }
    }

    static void initDB() {
        MySQL::Connector::registerConnector();
        try {
            _pSession = new Session(MySQL::Connector::KEY, _dbConnString);
        } catch(ConnectionFailedException& ex) {
            std::cout << ex.displayText() << std::endl;
            std::cout << "Try to connect without DB and create one ..." << std::endl;
            connectNoDB();
            try {
                _pSession = new Session(MySQL::Connector::KEY, _dbConnString);
            }
            catch (ConnectionFailedException& ex) {
                std::cout << ex.displayText() << std::endl;
                ASSERT_TRUE(false);
            }
        }
    }

    static void dropTable(const std::string& tableName) {
        try { *_pSession << Poco::format("DROP TABLE IF EXISTS %s", tableName), now; }
        catch(ConnectionException& ce){ std::cout << ce.displayText() << std::endl; 
        ASSERT_TRUE(false); }
        catch(StatementException& se){ std::cout << se.displayText() << std::endl; 
        ASSERT_TRUE(false); }
    }

    static void execSQL(Statement& exec_stmt) {
        try {
            exec_stmt, now; 
        } catch(ConnectionException& ce){
            std::cout << ce.displayText() << std::endl;
            ASSERT_TRUE(false); 
        } catch(StatementException& se){ 
            std::cout << se.displayText() << std::endl;
            ASSERT_TRUE(false); 
        }
    } 

    static void SetUpTestCase(){
        initDB();
        std::cout << "Setup..." << std::endl;
        std::cout << _dbConnString << std::endl;
    }
    
    static void TearDownTestCase(){
        std::cout << "Teardown..." << std::endl;
    }

static Poco::SharedPtr<Session> _pSession;
static std::string _dbConnString;
using Person = Poco::Tuple<std::string, std::string, std::string, int>;
};

Poco::SharedPtr<Session> MySQLTestSuites::_pSession = nullptr;
std::string MySQLTestSuites::_dbConnString =  "host=127.0.0.1"
	";user=root"
	";password=root"
	";db=stu_db"
	";compress=true"
	";auto-reconnect=true"
	";secure-auth=true"
	";protocol=tcp"; 


TEST_F(MySQLTestSuites, TestCreateTable) {
    std::cout << "Create Table..." << std::endl;
    dropTable("Person");
	auto createPersonStmt = (*_pSession << "CREATE TABLE Person (LastName VARCHAR(30), FirstName VARCHAR(30), Address VARCHAR(30), Age INTEGER)");
    execSQL(createPersonStmt);
}


TEST_F(MySQLTestSuites, Tuple) {
    std::cout << "Tuple..." << std::endl;
    Person p("Fredric", "Zhu", "ShangHai", 35);

    auto delete_stmt = (*_pSession << "delete from Person");
    execSQL(delete_stmt);

    auto insert_stmt = (*_pSession << "insert into Person(LastName, FirstName, Address, Age) values(?, ?, ?, ?)", 
        use(p));
    execSQL(insert_stmt);
   

    Person ret("", "", "", 0);
    ASSERT_TRUE(ret != p);

    auto select_stmt = (*_pSession << "select * from Person", into(ret));
    execSQL(select_stmt);
    
    ASSERT_TRUE(ret == p);
}


TEST_F(MySQLTestSuites, Tuples) {
    std::cout << "Tuples..." << std::endl;
    std::vector<Person> persons;
    Person fredric("Fredric", "Zhu", "ShangHai", 35);
    Person lily("Lily", "Hu", "WuHan", 33);
    Person feifei("YunFei", "Zhu", "WuHan", 4);
    persons.push_back(fredric);
    persons.push_back(lily);
    persons.push_back(feifei);

    auto delete_stmt = (*_pSession << "delete from Person");
    execSQL(delete_stmt);

    auto insert_stmt = (*_pSession << "insert into Person(LastName, FirstName, Address, Age) values(?, ?, ?, ?)",
        use(persons));
    execSQL(insert_stmt);

    int count = 0;
    auto count_stmt = (*_pSession << "select count(*) from Person", into(count));
    execSQL(count_stmt);
    ASSERT_TRUE(persons.size() == (std::size_t)count);

    std::vector<Person> ret;
    auto select_stmt = (*_pSession << "select * from Person", into(ret));
    execSQL(select_stmt);
    ASSERT_TRUE(ret == persons);

}
