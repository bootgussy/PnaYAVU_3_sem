#include "MenuOption.h"

MenuOption::MenuOption(const std::string& optionName, double optionPrice, int optionDiscount)
    : name(optionName), price(optionPrice), discount(optionDiscount) {}

MenuOption::MenuOption() : name(""), price(0.0), discount(0) {}

std::string MenuOption::getName() const
{
    return name;
}

double MenuOption::getPrice() const
{
    return price;
}

int MenuOption::getDiscount() const
{
    return discount;
}

bool MenuOption::operator!=(const MenuOption& right) const{
    if (this->getName() == right.getName() &&
        this->getPrice() == right.getPrice() &&
        this->getDiscount() == right.getDiscount())
    {
        return false;
    }
    else
    {
        return true;
    }
}
