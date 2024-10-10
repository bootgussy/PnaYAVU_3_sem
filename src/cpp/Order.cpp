#include "../header/Order.h"

void Order::addOption(const MenuOption& option)
{
    if (&option) {
        orderedOptions.push_back(option);
        totalCost += option.getPrice();
    }
}
