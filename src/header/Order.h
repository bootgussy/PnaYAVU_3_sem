#pragma once
#include <vector>
#include "../header/MenuOption.h"

class Order
{
public:
    std::vector<MenuOption> orderedOptions;
    double totalCost = 0.0;

    void addOption(const MenuOption& item);
};
