#pragma once
#include <iostream>
#include <string>
#include <sqlite3.h>
#include "../header/Account.h"
#include "../header/MenuOption.h"

class Database
{
public:
	Database(const std::string& databaseName);
	Database();
	~Database();

	static Database* getInstance();

	void createTableAccounts();
	void createTableMenu();

	sqlite3* getDatabase();

	bool addAccount(const std::string& login, const std::string& password, int points);
	Account getAccount(const std::string& login, const std::string& password);
	void updateAccount(std::string login, int points);

	bool addCategory(const std::string& category);
	bool addOptionToCategory(const std::string& category, const std::string& option, double price);
	std::string getCategory(int categoryId);
	MenuOption getOption(int categoryId, int optionId);
	int categoriesSize();
	int optionsSize();
	bool isOptionInCategory(int categoryId, int optionId);

private:
	sqlite3* DB;
	static Database* instance;
	sqlite3_stmt* stmt;
};