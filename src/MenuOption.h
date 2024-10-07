#pragma once
#include <string>

class MenuOption
{
    std::string name;
    double price;

public:
    MenuOption(const std::string& optionName, double optionPrice);
    MenuOption();
    std::string getName() const;
    double getPrice() const;
    bool operator!=(const MenuOption& right);
    friend MenuOption Database::getOption(int categoryId, int optionId);
};
