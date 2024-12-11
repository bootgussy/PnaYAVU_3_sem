#include "Menu.h"
#include "Order.h"
#include "Database.h"
#include "MenuOption.h"
#include <vector>
#include "sqlite3.h"

using namespace std;

Menu::Menu()
{

}

vector<MenuOption> Menu::displayOptions(int categoryId) const
{
    vector<MenuOption> options;
    MenuOption currentOption;

    for (int optionID : Database::getInstance()->isOptionInCategory(categoryId))
    {
        currentOption = Database::getInstance()->getOption(categoryId, optionID);
        options.push_back(currentOption);
    }
    return options;
}

double Menu::GetOrderTotalCost(Order const& order) const
{
    return order.totalCost;
}
