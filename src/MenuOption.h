#pragma once
#include <string>

class MenuOption
{
    std::string name;
    double price;
    int discount;

public:
    MenuOption(const std::string& optionName, double optionPrice, int optionDiscount);
    MenuOption();
    std::string getName() const;
    double getPrice() const;
    int getDiscount() const;

    bool operator!=(const MenuOption& right) const;
};
