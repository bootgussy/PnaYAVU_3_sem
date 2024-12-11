#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Order.h"
#include "Database.h"

class Menu
{
public:
    Menu();

    std::vector<MenuOption> displayOptions(int categoryId) const;
    double GetOrderTotalCost(Order const& order) const;

private:
    sqlite3* database = Database::getInstance()->getDatabase();
    sqlite3_stmt* stmt;
    std::vector<int> numOptionInDB;
};
