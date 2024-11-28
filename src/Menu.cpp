#include "Menu.h"
#include "Order.h"
#include "Database.h"
#include "MenuOption.h"
#include <vector>
#include "sqlite3.h"

using namespace std;

Menu::Menu()
{
    Database::getInstance()->addCategory("Drinks");
    Database::getInstance()->addCategory("Desserts");
    Database::getInstance()->addCategory("Combo");

    Database::getInstance()->addOptionToCategory("Drinks", "Cappuccino", 5.5, 0);
    Database::getInstance()->addOptionToCategory("Drinks", "Latte", 6.0, 0);
    Database::getInstance()->addOptionToCategory("Desserts", "Cheesecake", 4.5, 0);
    Database::getInstance()->addOptionToCategory("Desserts", "Tiramisu", 5.0, 0);
}

std::vector<int> Menu::displayMenu() const
{
    int categoryNum = 1;

    cout << "Menu:\n";
    for (int categoriesId : Database::getInstance()->getCategories())
    {
        cout << categoryNum << ". " << Database::getInstance()->getCategory(categoriesId) << "\n";
        categoryNum++;
    }
    return Database::getInstance()->getCategories();
}

MenuOption Menu::selectOption()
{
    int categoryChoice;
    int optionChoice;

    vector<int> categories = displayMenu();

    cout << "Select category (enter number): ";
    cin >> categoryChoice;

    while (categoryChoice < 1 || categoryChoice > Database::getInstance()->categoriesSize())
    {
        cout << "Please write correct number (1-" << Database::getInstance()->categoriesSize() << "): ";
        cin >> categoryChoice;
    }

    if (Database::getInstance()->optionsInCategory(categories[categoryChoice - 1]) > 0)
    {
        displayOptions(categories[categoryChoice - 1]);

        cout << "Select option (enter number): ";
        cin >> optionChoice;

        while (optionChoice < 1 || optionChoice > Database::getInstance()->optionsInCategory(categories[categoryChoice - 1]))
        {
            cout << "Please write correct number (1-" << Database::getInstance()->optionsInCategory(categories[categoryChoice - 1]) << "): ";
            cin >> optionChoice;
        }

        MenuOption selectedOption = Database::getInstance()->getOption(categoryChoice, numOptionInDB[optionChoice - 1]);
        if (selectedOption != MenuOption())
        {
            return selectedOption;
        }
        else
        {
            cout << "Invalid option selection!\n";
        }
    }
    else
    {
        cout << "No options in category" << endl;
    }

    return MenuOption();
}

Order Menu::addToOrder(Order& order)
{
    if (MenuOption option = selectOption(); option != MenuOption())
    {
        order.addOption(option);
    }
    return order;
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

void Menu::finishOrder(Order const& order) const
{
    cout << "Your order:\n";
    for (const auto& option : order.orderedOptions)
    {
        if (option.getDiscount() == 0)
        {
            cout << "- " << option.getName() << " : $" << option.getPrice() << '\n';
        }
        else
        {
            cout << "- " << option.getName() << " : $" << option.getPrice() / 100.0 * (100 - option.getDiscount()) << " (Discount " << option.getDiscount() << "%)" << '\n';
        }
    }
    cout << "Total: $" << order.totalCost << '\n';
}

double Menu::GetOrderTotalCost(Order const& order) const
{
    return order.totalCost;
}

Order Menu::deleteOption(Order order) const
{
    int deleteChoice;
    int optionNumber = 0;

    cout << "Your order:\n";
    for (const auto& option : order.orderedOptions)
    {
        ++optionNumber;
        if (option.getDiscount() == 0)
        {
            cout << optionNumber << ". " << option.getName() << " : $" << option.getPrice() << '\n';
        }
        else
        {
            cout << optionNumber << ". " << option.getName() << " : $" << option.getPrice() / 100.0 * (100 - option.getDiscount()) << " (Discount " << option.getDiscount() << "%)" << '\n';
        }
    }

    cout << "Select the option to remove: ";
    cin >> deleteChoice;

    while (deleteChoice < 1 || deleteChoice > order.orderedOptions.size())
    {
        cout << "Error. Please enter a valid option number:\n";
        cin >> deleteChoice;
    }

    cout << endl;
    order.totalCost -= order.orderedOptions[deleteChoice - 1].getPrice() / 100.0 * (100 - order.orderedOptions[deleteChoice - 1].getDiscount());
    order.orderedOptions.erase(order.orderedOptions.begin() + deleteChoice - 1);
    return order;
}
