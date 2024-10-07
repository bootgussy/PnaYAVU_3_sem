#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Order.h"
#include "Category.h"
#include "Database.h"
#include <vector>

class Menu
{
public:
    Menu();

    void displayMenu();
    void selectOption();
    void displayOptions(int id);
    void finishOrder() const;
    double GetOrderTotalCost() const;
    void deleteOption();

private:
    Order order;
    std::vector<Category*> categories;
    sqlite3* database = Database::getInstance()->getDatabase();
    sqlite3_stmt* stmt;
    std::vector<int> numOptionInDB;
};
