#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Category.h"
#include "Order.h"

class Menu
{
public:
    Menu();

    void addCategory(const std::string& categoryName);
    void addOptionToCategory(const std::string& categoryName, const std::string& optionName, double price) const;
    void displayMenu() const;
    void selectOption();
    void finishOrder() const;
    void deleteOption();

private:
    std::vector<Category*> categories;
    Order order;
};
