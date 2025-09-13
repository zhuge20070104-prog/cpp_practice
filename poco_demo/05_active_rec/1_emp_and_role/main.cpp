#include "Poco/ActiveRecord/Context.h"
#include "Poco/ActiveRecord/Query.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Data/Statement.h"
#include "Poco/UUIDGenerator.h"
#include "Sample/Employee.h"
#include "Sample/Role.h"
#include "gtest/gtest.h"


using namespace std::string_literals;
using namespace Poco::Data::Keywords;
using Poco::ActiveRecord::Context;
using Poco::ActiveRecord::Query;
using Sample::Employee;
using Sample::Role;


int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

class SQLiteTestSuites: public testing::Test {
public:
    static void SetUpTestCase(){
        Poco::Data::SQLite::Connector::registerConnector();
    }
    
    static void TearDownTestCase(){
        Poco::Data::SQLite::Connector::unregisterConnector();
    }

	static void createTable() {
		Poco::Data::Session session(s_connect, s_db);

		session << "DROP TABLE IF EXISTS employees", now;
		session << "DROP TABLE IF EXISTS roles", now;
		session
			<< "CREATE TABLE employees ("
			<< "  id CHAR(36),"
			<< "  name VARCHAR(64),"
			<< "  ssn VARCHAR(32),"
			<< "  role INTEGER,"
			<< "  manager CHAR(36)"
			<< ")",
			now;
		session
			<< "CREATE TABLE roles ("
			<< "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
			<< "  name VARCHAR(64),"
			<< "  description VARCHAR(256)"
			<< ")",
		now;
	}

	static void createRoles(Poco::ActiveRecord::Context::Ptr pContext) {
		Role::Ptr pDeveloper = new Role();
		pDeveloper->name("Developer").description("Developer role");
		pDeveloper->create(pContext);

		Role::Ptr pSeniorDeveloper = new Role();
		pSeniorDeveloper->name("Senior Developer").description("Senior developer role");
		pSeniorDeveloper->create(pContext);

		Role::Ptr pManager = new Role();
		pManager->name("Manager").description("Manager role");
		pManager->create(pContext);
	}

    static std::string s_connect;
    static std::string s_db;
};

std::string SQLiteTestSuites::s_connect = "SQLite";
std::string SQLiteTestSuites::s_db = "data.sqlite";

TEST_F(SQLiteTestSuites, TestInsert) {
	createTable();

    Poco::Data::Session session(s_connect, s_db);
	Context::Ptr pContext = new Context(session);
	Role::Ptr pDeveloper = new Role;
	pDeveloper->name("Developer").description("Developer role");

	ASSERT_TRUE(!pDeveloper->isValid());

	pDeveloper->create(pContext);

	ASSERT_TRUE (pDeveloper->isValid());

	int n = 0;
	session << "SELECT COUNT(*) FROM roles", into(n), now;
	ASSERT_TRUE (n == 1);

	ASSERT_TRUE(pDeveloper->id() == 1);

	Role::Ptr pSeniorDeveloper = new Role;
	pSeniorDeveloper->name("Senior Developer").description("Senior developer role");

	pSeniorDeveloper->create(pContext);

	session << "SELECT COUNT(*) FROM roles", into(n), now;
	ASSERT_TRUE (n == 2);

	ASSERT_TRUE (pSeniorDeveloper->id() == 2);
}

TEST_F(SQLiteTestSuites, TestFind) {
	createTable();

	Poco::Data::Session session(s_connect, s_db);
	
	Context::Ptr pContext = new Context(session);
	createRoles(pContext);

	Role::Ptr pRole = Role::find(pContext, 1);
	ASSERT_TRUE(!pRole.isNull());
	ASSERT_TRUE(pRole->name() == "Developer");
	ASSERT_TRUE(pRole->description() == "Developer role");

	pRole = Role::find(pContext, 2);
	ASSERT_TRUE(!pRole.isNull());
	ASSERT_TRUE(pRole->name() == "Senior Developer");
	ASSERT_TRUE(pRole->description() == "Senior developer role");

	pRole = Role::find(pContext, 3);
	ASSERT_TRUE(!pRole.isNull());
	ASSERT_TRUE(pRole->name() == "Manager");
	ASSERT_TRUE(pRole->description() == "Manager role");

	pRole = Role::find(pContext, 4);
	ASSERT_TRUE(pRole.isNull());
}

TEST_F(SQLiteTestSuites, TestUpdate) {
	createTable();
	Poco::Data::Session session(s_connect, s_db);
	Context::Ptr pContext = new Context(session);
	createRoles(pContext);

	Role::Ptr pRole = Role::find(pContext, 1);
	ASSERT_TRUE(!pRole.isNull());
	pRole->name("Junior Developer").description("Junior developer role");
	pRole->update();

	pRole = Role::find(pContext, 1);
	ASSERT_TRUE(!pRole.isNull());
	ASSERT_TRUE(pRole->name() == "Junior Developer");
	ASSERT_TRUE(pRole->description() == "Junior developer role");
}


TEST_F(SQLiteTestSuites, TestDelete) {
	createTable();
	Poco::Data::Session session(s_connect, s_db);
	Context::Ptr pContext = new Context(session);
	createRoles(pContext);

	Role::Ptr pRole = Role::find(pContext, 1);
	ASSERT_TRUE(!pRole.isNull());

	pRole->remove();
	pRole = Role::find(pContext, 1);
	ASSERT_TRUE(pRole.isNull());
}

TEST_F(SQLiteTestSuites, TestRelations) {
	createTable();
	Poco::Data::Session session(s_connect, s_db);
	Context::Ptr pContext = new Context(session);
	
	createRoles(pContext);
	Employee::Ptr pManager = new Employee(Poco::UUIDGenerator().createOne());
	pManager->name("Bill Lumbergh").ssn("23452343").roleID(3);
	pManager->create(pContext);

	Role::Ptr pManagerRole = pManager->role();
	ASSERT_FALSE(pManagerRole.isNull());
	ASSERT_TRUE(pManagerRole->id() == 3);

	Employee::Ptr pEmployee = new Employee(Poco::UUIDGenerator().createOne());
	pEmployee->name("Michael Bolton").ssn("123987123").roleID(2).manager(pManager);
	pEmployee->create(pContext);
	ASSERT_TRUE(pEmployee->managerID() == pManager->id());
}

TEST_F(SQLiteTestSuites, TestQuery) {
	createTable();
	Poco::Data::Session session(s_connect, s_db);
	Context::Ptr pContext = new Context(session);

	createRoles(pContext);
	Query<Role> query(pContext);
	auto result = query.execute();
	ASSERT_TRUE(result.size() == 3);
}

TEST_F(SQLiteTestSuites, TestQueryWhere) {
	createTable();
	Poco::Data::Session session(s_connect, s_db);
	Context::Ptr pContext = new Context(session);
	createRoles(pContext);

	Query<Role> query(pContext);
	query.where("name = 'Senior Developer'");

	auto result = query.execute();
	ASSERT_TRUE(result.size() == 1);
	ASSERT_TRUE(result[0]->name() == "Senior Developer");
}


TEST_F(SQLiteTestSuites, TestQueryWhereBind) {
	createTable();
	Poco::Data::Session session(s_connect, s_db);
	Context::Ptr pContext = new Context(session);
	createRoles(pContext);

	Query<Role> query(pContext);
	query.where("name = ?").bind("Senior Developer"s);

	auto result = query.execute();
	ASSERT_TRUE(result.size() == 1);
	ASSERT_TRUE(result[0]->name() == "Senior Developer");
}


TEST_F(SQLiteTestSuites, TestQueryFilter) {
	createTable();
	Poco::Data::Session session(s_connect, s_db);
	Context::Ptr pContext = new Context(session);
	createRoles(pContext);

	Query<Role> query(pContext);
	query.filter([](Role const& role) {
		return role.name() == "Senior Developer";
	});

	auto result = query.execute();
	ASSERT_TRUE(result.size() == 1);
	ASSERT_TRUE(result[0]->name() == "Senior Developer");
}


TEST_F(SQLiteTestSuites, TestQueryOrderedBy) {
	createTable();
	Poco::Data::Session session(s_connect, s_db);
	Context::Ptr pContext = new Context(session);
	createRoles(pContext);

	Query<Role> query(pContext);
	query.orderBy("id DESC");

	auto result = query.execute();
	ASSERT_TRUE(result.size() == 3);
	ASSERT_TRUE(result[0]->name() == "Manager");
}

TEST_F(SQLiteTestSuites, TestQueryPaging) {
	createTable();
	Poco::Data::Session session(s_connect, s_db);
	Context::Ptr pContext = new Context(session);
	createRoles(pContext);

	Query<Role> query(pContext);
	auto result = query.orderBy("id").offset(0).limit(2).execute();
	ASSERT_TRUE(result.size() == 2);
	ASSERT_TRUE(result[0]->name() == "Developer");
	ASSERT_TRUE(result[1]->name() == "Senior Developer");

	query.reset();
	result = query.orderBy("id").offset(1).limit(2).execute();
	ASSERT_TRUE(result.size() == 2);
	ASSERT_TRUE(result[0]->name() == "Senior Developer");
	ASSERT_TRUE(result[1]->name() == "Manager");
}