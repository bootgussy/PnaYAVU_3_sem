#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../header/Account.h"
#include "Database.h"

class LoyaltySystem
{
private:
    sqlite3* database = Database::getInstance()->getDatabase();
    sqlite3_stmt* stmt;

public:
    LoyaltySystem();
    void redeemPoints(std::shared_ptr<Account> account, double totalCost) const;
};
