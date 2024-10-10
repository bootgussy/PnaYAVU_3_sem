#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "../header/Order.h"
#include "../header/Database.h"

class Menu
{
public:
    Menu();

    void displayMenu() const;
    void selectOption();
    void displayOptions(int id);
    void finishOrder() const;
    double GetOrderTotalCost() const;
    void deleteOption();

private:
    Order order;
    sqlite3* database = Database::getInstance()->getDatabase();
    sqlite3_stmt* stmt;
    std::vector<int> numOptionInDB;
};
