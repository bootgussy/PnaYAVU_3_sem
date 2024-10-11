#include "../header/MenuOption.h"

MenuOption::MenuOption(const std::string& optionName, double optionPrice)
    : name(optionName), price(optionPrice) {}

MenuOption::MenuOption() = default;

std::string MenuOption::getName() const
{
    return name;
}

double MenuOption::getPrice() const
{
    return price;
}

bool MenuOption::operator!=(const MenuOption& right) const{
    if (this->getName() == right.getName() && this->getPrice() == right.getPrice())
    {
        return false;
    }
    else
    {
        return true;
    }
}
