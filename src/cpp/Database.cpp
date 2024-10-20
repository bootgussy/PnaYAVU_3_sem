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
		"POINTS INT NOT NULL, "
		"ROLE TEXT NOT NULL);";
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
		"DISCOUNT INT NOT NULL,"
		"CATEGORY_ID INTEGER,"
		"FOREIGN KEY(CATEGORY_ID) REFERENCES CATEGORIES(ID));";
	sqlite3_exec(DB, createTableOptionsSQL, nullptr, nullptr, nullptr);
}

sqlite3* Database::getDatabase()
{
	return DB;
}

bool Database::addAccount(const std::string& login, const std::string& password, int points, const std::string& role)
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
		std::string insertAccountSQL = "INSERT INTO ACCOUNTS (LOGIN, PASSWORD, POINTS, ROLE) VALUES(?, ?, ?, ?)";
		sqlite3_prepare_v2(DB, insertAccountSQL.c_str(), -1, &stmt, nullptr);

		sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 3, points);
		sqlite3_bind_text(stmt, 4, role.c_str(), -1, SQLITE_STATIC);

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
			sqlite3_column_int(stmt, 3),
			reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))
		);
		sqlite3_finalize(stmt);
		return account;
	}
	sqlite3_finalize(stmt);
	return Account();
}

Account Database::getAccount(int id)
{
	sqlite3* db = getDatabase();
	std::string searchUserSQL = "SELECT * FROM ACCOUNTS WHERE ACCOUNT_ID = ?;";
	sqlite3_prepare_v2(db, searchUserSQL.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_int(stmt, 1, id);

	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		Account account(
			reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
			reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
			sqlite3_column_int(stmt, 3),
			reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))
		);
		sqlite3_finalize(stmt);
		return account;
	}
	sqlite3_finalize(stmt);
	return Account("", "", 0, "");
}

void Database::updateAccount(const std::string& login, int points)
{
	std::string searchLoginSQL = "UPDATE ACCOUNTS SET POINTS = ? WHERE LOGIN = ?;";
	sqlite3_prepare_v2(DB, searchLoginSQL.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_int(stmt, 1, points);
	sqlite3_bind_text(stmt, 2, login.c_str(), -1, SQLITE_STATIC);

	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
}

void Database::setRole(int id, const std::string& role)
{
	std::string searchLoginSQL = "UPDATE ACCOUNTS SET ROLE = ? WHERE ACCOUNT_ID = ?;";
	sqlite3_prepare_v2(DB, searchLoginSQL.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_text(stmt, 1, role.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 2, id);
	
	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
}

bool Database::addCategory(const std::string& category)
{
	std::string searchCategorySQL = "SELECT * FROM CATEGORIES WHERE NAME = ?;";
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

bool Database::addOptionToCategory(const std::string& category, const std::string& option, double price, int discount)
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
		std::string insertOptionToCategorySQL = "INSERT INTO OPTIONS (NAME, PRICE, DISCOUNT, CATEGORY_ID) VALUES(?, ?, ?, ?);";
		sqlite3_prepare_v2(DB, insertOptionToCategorySQL.c_str(), -1, &stmt, nullptr);

		sqlite3_bind_text(stmt, 1, option.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_double(stmt, 2, price);
		sqlite3_bind_int(stmt, 3, discount);
		sqlite3_bind_int(stmt, 4, categoryId);

		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
		return true;
	}
}

std::vector<int> Database::getCategories()
{
	std::vector<int> categoriesId;
	std::string searchCategorySQL = "SELECT * FROM CATEGORIES;";
	sqlite3_prepare_v2(DB, searchCategorySQL.c_str(), -1, &stmt, nullptr);

	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		categoriesId.push_back(sqlite3_column_int(stmt, 0));
	}
	sqlite3_finalize(stmt);
	return categoriesId;
}

std::string Database::getCategory(int categoryId)
{
	std::string searchCategorySQL = "SELECT * FROM CATEGORIES WHERE ID = ?;";
	sqlite3_prepare_v2(DB, searchCategorySQL.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_int(stmt, 1, categoryId);

	sqlite3_step(stmt);
	
	return reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
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
		    sqlite3_column_double(statement, 2),
			sqlite3_column_int(statement, 3)
		);
		sqlite3_finalize(statement);
		return option;
	}
	sqlite3_finalize(statement);
	return MenuOption();
}

int Database::categoriesSize()
{
	std::string size = "SELECT COUNT(*) FROM CATEGORIES;";
	sqlite3_prepare_v2(DB, size.c_str(), -1, &stmt, nullptr);
	sqlite3_step(stmt);
	return sqlite3_column_int(stmt, 0);
}

int Database::optionsSize()
{
	std::string size = "SELECT COUNT(*) FROM OPTIONS;";
	sqlite3_prepare_v2(DB, size.c_str(), -1, &stmt, nullptr);
	sqlite3_step(stmt);
	return sqlite3_column_int(stmt, 0);
}

int Database::optionsInCategory(int categoryId)
{
	std::string size = "SELECT COUNT(*) FROM OPTIONS WHERE CATEGORY_ID = ?;";
	sqlite3_prepare_v2(DB, size.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_int(stmt, 1, categoryId);

	sqlite3_step(stmt);

	return sqlite3_column_int(stmt, 0);
}

std::vector<int> Database::isOptionInCategory(int categoryId)
{
	std::string searchOptionSQL = "SELECT * FROM OPTIONS WHERE CATEGORY_ID = ?;";
	sqlite3_prepare_v2(DB, searchOptionSQL.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_int(stmt, 1, categoryId);

	std::vector<int> optionsID;

	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		optionsID.push_back(sqlite3_column_int(stmt, 0));
	}
	return optionsID;
}

void Database::setPrice(const std::string& name, double newPrice)
{
	std::string searchOptionSQL = "UPDATE OPTIONS SET PRICE = ? WHERE NAME = ?;";
	sqlite3_prepare_v2(DB, searchOptionSQL.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_double(stmt, 1, newPrice);
	sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);

	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
}

void Database::setDiscount(const std::string& name, int newDiscount)
{
	std::string searchOptionSQL = "UPDATE OPTIONS SET DISCOUNT = ? WHERE NAME = ?;";
	sqlite3_prepare_v2(DB, searchOptionSQL.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_int(stmt, 1, newDiscount);
	sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);

	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
}

void Database::deleteOption(const std::string& name)
{
	std::string searchOptionSQL = "DELETE FROM OPTIONS WHERE NAME = ?;";
	sqlite3_prepare_v2(DB, searchOptionSQL.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
}

void Database::addCombo(const std::string& comboName, const Order order, double totalCost)
{
	std::string category;
	category = "Combo";	
	
	std::string searchComboIdSQL = "SELECT * FROM OPTIONS WHERE NAME = ?;";
	sqlite3_prepare_v2(DB, searchComboIdSQL.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_text(stmt, 1, comboName.c_str(), -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		std::cout << "This combo exists" << std::endl;
	}
	else
	{
		sqlite3_finalize(stmt);

		addOptionToCategory(category, comboName, totalCost, 0);

		searchComboIdSQL = "SELECT * FROM OPTIONS WHERE NAME = ?;";
		sqlite3_prepare_v2(DB, searchComboIdSQL.c_str(), -1, &stmt, nullptr);

		sqlite3_bind_text(stmt, 1, comboName.c_str(), -1, SQLITE_STATIC);

		sqlite3_step(stmt);
		int comboId = sqlite3_column_int(stmt, 0);

		sqlite3_finalize(stmt);

		const char* createTableComboSQL =
			"CREATE TABLE IF NOT EXISTS COMBO("
			"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
			"OPTIONS INT NOT NULL, "
			"OPTION_ID INT NOT NULL, "
			"FOREIGN KEY(OPTION_ID) REFERENCES OPTIONS(ID));";

		sqlite3_exec(DB, createTableComboSQL, nullptr, nullptr, nullptr);

		for (MenuOption option : order.orderedOptions)
		{
			std::string searchCategoryIdSQL = "SELECT * FROM OPTIONS WHERE NAME = ?;";
			sqlite3_prepare_v2(DB, searchCategoryIdSQL.c_str(), -1, &stmt, nullptr);

			sqlite3_bind_text(stmt, 1, option.getName().c_str(), -1, SQLITE_STATIC);

			sqlite3_step(stmt);

			int optionId = sqlite3_column_int(stmt, 0);
			sqlite3_finalize(stmt);

			std::string searchIdSQL = "SELECT * FROM COMBO WHERE OPTIONS = ? AND OPTION_ID = ?";
			sqlite3_prepare_v2(DB, searchIdSQL.c_str(), -1, &stmt, nullptr);

			sqlite3_bind_int(stmt, 1, optionId);
			sqlite3_bind_int(stmt, 2, comboId);

			if (sqlite3_step(stmt) == SQLITE_ROW)
			{
				sqlite3_finalize(stmt);
			}
			else
			{
				sqlite3_finalize(stmt);
				std::string insertOptionToCategorySQL = "INSERT INTO COMBO (OPTIONS, OPTION_ID) VALUES(?, ?);";
				sqlite3_prepare_v2(DB, insertOptionToCategorySQL.c_str(), -1, &stmt, nullptr);

				sqlite3_bind_int(stmt, 1, optionId);
				sqlite3_bind_int(stmt, 2, comboId);

				sqlite3_step(stmt);
				sqlite3_finalize(stmt);
			}
		}
	}
}