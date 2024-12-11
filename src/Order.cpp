#include "Order.h"
#include <cmath>

void Order::addOption(const MenuOption& option)
{
    if (&option) {
        orderedOptions.push_back(option);

        totalCost += option.getPrice() - (option.getPrice() / 100.0 * option.getDiscount());
        totalCost = round(totalCost * 100) / 100;
    }
}

void Order::deleteOption(int index)
{
    totalCost -= orderedOptions[index].getPrice() - (orderedOptions[index].getPrice() / 100.0 * orderedOptions[index].getDiscount());
    totalCost = round(totalCost * 100) / 100;

    orderedOptions.erase(orderedOptions.cbegin() + index);
}

void Order::clearOrder()
{
    orderedOptions.clear();
    totalCost = 0;
}
