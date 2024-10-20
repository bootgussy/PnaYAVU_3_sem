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

    std::vector<int> displayMenu() const;
    MenuOption selectOption();
    Order addToOrder(Order& order);
    void displayOptions(int id);
    void finishOrder(Order const& order) const;
    double GetOrderTotalCost(Order const& order) const;
    Order deleteOption(Order order) const;

private:
    sqlite3* database = Database::getInstance()->getDatabase();
    sqlite3_stmt* stmt;
    std::vector<int> numOptionInDB;
};
