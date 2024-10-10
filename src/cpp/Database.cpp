#include "../header/Database.h"
#include "../header/LoyaltySystem.h"
#include "../header/MenuOption.h"
#include <sqlite3.h>

Database::Database()
{
	std::string databaseName = "CoffeeHouse.db";
	sqlite3_open(databaseName.c_str(), &DB);

	createTableAccounts();
	createTableMenu();
}

Database::~Database()
{
	sqlite3_close(DB);
}

std::unique_ptr<Database> Database::instance = nullptr;

Database* Database::getInstance() {
	if (instance == nullptr) {
		instance = std::make_unique<Database>();
	}
	return instance.get();
}

void Database::createTableAccounts()
{
	const char* createTableAccountsSQL =
		"CREATE TABLE IF NOT EXISTS ACCOUNTS("
		"ACCOUNT_ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"LOGIN TEXT NOT NULL, "
		"PASSWORD TEXT NOT NULL, "
		"POINTS INT NOT NULL);";
	sqlite3_exec(DB, createTableAccountsSQL, nullptr, nullptr, nullptr);
}

void Database::createTableMenu()
{
	const char* createTableCategoriesSQL =
		"CREATE TABLE IF NOT EXISTS CATEGORIES ("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"NAME TEXT NOT NULL);";
	sqlite3_exec(DB, createTableCategoriesSQL, nullptr, nullptr, nullptr);

	const char* createTableOptionsSQL =
		"CREATE TABLE IF NOT EXISTS OPTIONS ("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"NAME TEXT NOT NULL,"
		"PRICE REAL NOT NULL,"
		"CATEGORY_ID INTEGER,"
		"FOREIGN KEY(CATEGORY_ID) REFERENCES CATEGORIES(ID));";
	sqlite3_exec(DB, createTableOptionsSQL, nullptr, nullptr, nullptr);
}

sqlite3* Database::getDatabase()
{
	return DB;
}

bool Database::addAccount(const std::string& login, const std::string& password, int points)
{
	std::string searchLoginSQL = "SELECT * FROM ACCOUNTS WHERE LOGIN = ?";
	sqlite3_prepare_v2(DB, searchLoginSQL.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		sqlite3_finalize(stmt);
		return false;
	}
	else
	{
		std::string insertAccountSQL = "INSERT INTO ACCOUNTS (LOGIN, PASSWORD, POINTS) VALUES(?, ?, ?)";
		sqlite3_prepare_v2(DB, insertAccountSQL.c_str(), -1, &stmt, nullptr);

		sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 3, points);

		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
		return true;
	}
}

Account Database::getAccount(const std::string& login, const std::string& password)
{
	sqlite3* db = getDatabase();
	std::string searchUserSQL = "SELECT * FROM ACCOUNTS WHERE LOGIN = ? AND PASSWORD = ?;";
	sqlite3_prepare_v2(db, searchUserSQL.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		Account account(
			reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
			reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
			sqlite3_column_int(stmt, 3)
		);
		sqlite3_finalize(stmt);
		return account;
	}
	sqlite3_finalize(stmt);
	return Account();
}

void Database::updateAccount(const std::string& login, int points)
{
	std::string searchLoginSQL = "UPDATE ACCOUNTS SET POINTS = ? WHERE LOGIN = ?;";
	sqlite3_prepare_v2(DB, searchLoginSQL.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_int(stmt, 1, points);
	sqlite3_bind_text(stmt, 2, login.c_str(), -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		std::cerr << "Error updating account: " << sqlite3_errmsg(DB) << std::endl;
	}
	sqlite3_finalize(stmt);
}

bool Database::addCategory(const std::string& category)
{
	std::string searchCategorySQL = "SELECT * FROM CATEGORIES WHERE NAME = ?; ";
	sqlite3_prepare_v2(DB, searchCategorySQL.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_text(stmt, 1, category.c_str(), -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		sqlite3_finalize(stmt);
		return false;
	}
	else
	{
		std::string insertCategorySQL = "INSERT INTO CATEGORIES (NAME) VALUES(?);";
		sqlite3_prepare_v2(DB, insertCategorySQL.c_str(), -1, &stmt, nullptr);

		sqlite3_bind_text(stmt, 1, category.c_str(), -1, SQLITE_STATIC);

		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
		return true;
	}
}

bool Database::addOptionToCategory(const std::string& category, const std::string& option, double price)
{
	std::string searchCategoryIdSQL = "SELECT * FROM CATEGORIES WHERE NAME = ?;";
	sqlite3_prepare_v2(DB, searchCategoryIdSQL.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_text(stmt, 1, category.c_str(), -1, SQLITE_STATIC);

	sqlite3_step(stmt);
    int categoryId = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);

	std::string searchOptionSQL = "SELECT * FROM OPTIONS WHERE CATEGORY_ID = ? AND NAME = ?;";
	sqlite3_prepare_v2(DB, searchOptionSQL.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_int(stmt, 1, categoryId);
	sqlite3_bind_text(stmt, 2, option.c_str(), -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		sqlite3_finalize(stmt);
		return false;
	}
	else
	{
		std::string insertOptionToCategorySQL = "INSERT INTO OPTIONS (NAME, PRICE, CATEGORY_ID) VALUES(?, ?, ?);";
		sqlite3_prepare_v2(DB, insertOptionToCategorySQL.c_str(), -1, &stmt, nullptr);

		sqlite3_bind_text(stmt, 1, option.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_double(stmt, 2, price);
		sqlite3_bind_int(stmt, 3, categoryId);

		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
		return true;
	}
}

std::string Database::getCategory(int categoryId)
{
	std::string searchCategorySQL = "SELECT * FROM CATEGORIES WHERE ID = ?;";
	std::string category;
	sqlite3_prepare_v2(DB, searchCategorySQL.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_int(stmt, 1, categoryId);

	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		category = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		sqlite3_finalize(stmt);
		return category;
	}
	sqlite3_finalize(stmt);
	return "NULL";
}

MenuOption Database::getOption(int categoryId, int optionId)
{
	sqlite3* db = getDatabase();
	sqlite3_stmt* statement;
	std::string searchOptionSQL = "SELECT * FROM OPTIONS WHERE CATEGORY_ID = ? AND ID = ?;";
	sqlite3_prepare_v2(db, searchOptionSQL.c_str(), -1, &statement, nullptr);

	sqlite3_bind_int(statement, 1, categoryId);
	sqlite3_bind_int(statement, 2, optionId);

	if (sqlite3_step(statement) == SQLITE_ROW)
	{
		MenuOption option(
			reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)),
		    sqlite3_column_double(statement, 2)
		);
		sqlite3_finalize(statement);
		return option;
	}
	sqlite3_finalize(statement);
	return MenuOption();
}

int Database::categoriesSize()
{
	std::string size = "SELECT COUNT(*) FROM CATEGORIES";
	sqlite3_prepare_v2(DB, size.c_str(), -1, &stmt, nullptr);
	sqlite3_step(stmt);
	return sqlite3_column_int(stmt, 0);
}

int Database::optionsSize()
{
	std::string size = "SELECT COUNT(*) FROM OPTIONS";
	sqlite3_prepare_v2(DB, size.c_str(), -1, &stmt, nullptr);
	sqlite3_step(stmt);
	return sqlite3_column_int(stmt, 0);
}

bool Database::isOptionInCategory(int categoryId, int optionId)
{
	std::string searchOptionSQL = "SELECT * FROM OPTIONS WHERE CATEGORY_ID = ? AND ID = ?;";
	sqlite3_prepare_v2(DB, searchOptionSQL.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_int(stmt, 1, categoryId);
	sqlite3_bind_int(stmt, 2, optionId);

	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		return true;
	}
	else
	{
		return false;
	}
}