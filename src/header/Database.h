#pragma once
#include <iostream>
#include <string>
#include <sqlite3.h>
#include <memory>
#include <vector>
#include "Account.h"
#include "MenuOption.h"
#include "Order.h"

class Database
{
public:
	Database();
	~Database();

	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;

	static Database* getInstance();

	void createTableAccounts();
	void createTableMenu();

	sqlite3* getDatabase();

	bool addAccount(const std::string& login, const std::string& password, int points, const std::string& role);
	Account getAccount(const std::string& login, const std::string& password);
	Account getAccount(int id);
	void updateAccount(const std::string& login, int points);
	void setRole(int id, const std::string& role);

	bool addCategory(const std::string& category);
	bool addOptionToCategory(const std::string& category, const std::string& option, double price, int discount);
	std::vector<int> getCategories();
	std::string getCategory(int categoryId);
	MenuOption getOption(int categoryId, int optionId);
	int categoriesSize();
	int optionsSize();
	int optionsInCategory(int categoryId);
	std::vector<int> isOptionInCategory(int categoryId);
	void setPrice(const std::string& name, double newPrice);
	void setDiscount(const std::string& name, int newDiscount);
	void deleteCategory(int categoryId);
	void deleteOption(const std::string& optionName);
	void addCombo(const std::string& comboName, Order const& order, double totalCost);

private:
	sqlite3* DB;
	static std::unique_ptr<Database> instance;
	sqlite3_stmt* stmt;
};