#pragma once

#include <sqlite3.h>
#include "Database.h"
#include "Person.h"

class Buyer : virtual public Person
{
private:
	sqlite3* database = Database::getInstance()->getDatabase();
	sqlite3_stmt* stmt;
	std::string name;
	double points;

public:
	Buyer();

	std::string getRole() const override;
	void redeemPoints(std::shared_ptr<Account> account, double totalCost) const;
};
