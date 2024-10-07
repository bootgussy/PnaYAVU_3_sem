#pragma once
#include <string>
#include <vector>
#include "MenuOption.h"

class Category
{
public:
    std::string name;
    std::vector<MenuOption*> options;

    explicit Category(const std::string& categoryName);
    void addOption(const std::string& optionName, double optionPrice);
    void displayOptions(int id);
    MenuOption* getOption(int index) const;
};
