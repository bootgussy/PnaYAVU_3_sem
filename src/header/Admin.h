#pragma once

#include <sqlite3.h>
#include "Database.h"
#include "Person.h"
#include "Manager.h"

class Admin : public Manager, public Person
{
private:
	sqlite3* database = Database::getInstance()->getDatabase();
	sqlite3_stmt* stmt;
	std::string name;

public:
	Admin();

	std::string getRole() const override;

	void changeRole() const;
};