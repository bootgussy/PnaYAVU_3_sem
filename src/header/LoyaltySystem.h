#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../header/Account.h"
#include "../header/Database.h"

class LoyaltySystem 
{
private:
    sqlite3* database = Database::getInstance()->getDatabase();
    sqlite3_stmt* stmt;

public:
    LoyaltySystem();
    std::shared_ptr<Account>  logIn();
    std::shared_ptr<Account>  signIn();
    void redeemPoints(std::shared_ptr<Account> account, double totalCost) const;
};
