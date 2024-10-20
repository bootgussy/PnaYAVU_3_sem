#pragma once

#include <sqlite3.h>
#include "Database.h"
#include "Person.h"

class Manager : public Person
{
private:
	sqlite3* database = Database::getInstance()->getDatabase();
	sqlite3_stmt* stmt;
	std::string name;

public:
	Manager();

	std::string getRole() const override;

	void changePrice();
	void addDiscounts();
	void removeDiscounts();
	void addCombo();
	void addCategoryToMenu();
	void addOptionToCategory();
	void removeOptionFromMenu();
};