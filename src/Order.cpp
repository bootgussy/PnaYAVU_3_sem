#include "Order.h"

void Order::addOption(MenuOption option)
{
    if (&option) {
        orderedOptions.push_back(option);
        totalCost += option.getPrice();
    }
}
