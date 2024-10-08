#include "MenuOption.h"

MenuOption::MenuOption(const std::string& optionName, double optionPrice)
    : name(optionName), price(optionPrice) {}

std::string MenuOption::GetName() const
{
    return name;
}

double MenuOption::GetPrice() const
{
    return price;
}
