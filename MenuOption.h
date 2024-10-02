#pragma once
#include <string>

class MenuOption
{
    std::string name;
    double price;

public:
    MenuOption(const std::string& optionName, double optionPrice);
    std::string GetName() const;
    double GetPrice() const;
};
