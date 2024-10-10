#include "../header/Menu.h"
#include "../header/Order.h"
#include "../header/Database.h"
#include "../header/MenuOption.h"
#include <vector>
#include <sqlite3.h>

using namespace std;

Menu::Menu()
{
    Database::getInstance()->addCategory("Drinks");
    Database::getInstance()->addCategory("Desserts");

    Database::getInstance()->addOptionToCategory("Drinks", "Cappuccino", 5.5);
    Database::getInstance()->addOptionToCategory("Drinks", "Latte", 6.0);
    Database::getInstance()->addOptionToCategory("Desserts", "Cheesecake", 4.5);
    Database::getInstance()->addOptionToCategory("Desserts", "Tiramisu", 5.0);
}

void Menu::displayMenu() const
{
    int categoryId = 1;

    cout << "Menu:\n";
    while (Database::getInstance()->getCategory(categoryId) != "NULL")
    {
        cout << categoryId << ". " << Database::getInstance()->getCategory(categoryId) << "\n";
        categoryId++;
    }
}

void Menu::selectOption()
{
    displayMenu();

    int categoryChoice;
    cout << "Select category (enter number): ";
    cin >> categoryChoice;

    if (categoryChoice > 0 && categoryChoice <= Database::getInstance()->categoriesSize())
    {
        displayOptions(categoryChoice);

        int optionChoice;
        cout << "Select option (enter number): ";
        cin >> optionChoice;

        MenuOption selectedOption = Database::getInstance()->getOption(categoryChoice, numOptionInDB[optionChoice - 1]);
        if (selectedOption != MenuOption())
        {
            order.addOption(selectedOption);
        }
        else
        {
            cout << "Invalid option selection!\n";
        }
    }
    else
    {
        cout << "Invalid category selection!\n";
    }
}

void Menu::displayOptions(int categoryId)
{
    numOptionInDB.clear();
    int numOptionInCategory = 1;

    cout << "Category: " << Database::getInstance()->getCategory(categoryId) << "\n";
    for (int optionId = 1; optionId <= Database::getInstance()->optionsSize(); optionId++)
        if (Database::getInstance()->isOptionInCategory(categoryId, optionId))
        {
            cout << numOptionInCategory << ". " << Database::getInstance()->getOption(categoryId, optionId).getName() << " - $" << Database::getInstance()->getOption(categoryId, optionId).getPrice() << '\n';
            numOptionInDB.push_back(optionId);
            numOptionInCategory++;
        }
    
}

void Menu::finishOrder() const
{
    cout << "Your order:\n";
    for (const auto& option : order.orderedOptions)
    {
        cout << "- " << option.getName() << " : $" << option.getPrice() << '\n';
    }
    cout << "Total: $" << order.totalCost << '\n';
}

double Menu::GetOrderTotalCost() const
{
    return order.totalCost;
}

void Menu::deleteOption()
{
    int deleteChoice;
    int optionNumber = 0;

    cout << "Your order:\n";
    for (const auto& option : order.orderedOptions)
    {
        ++optionNumber;
        cout << optionNumber << ". " << option.getName() << " : $" << option.getPrice() << '\n';
    }

    cout << "Select the option to remove:\n";
    cin >> deleteChoice;

    while (deleteChoice < 1 || deleteChoice > order.orderedOptions.size())
    {
        cout << "Error. Please enter a valid option number:\n";
        cin >> deleteChoice;
    }

    cout << endl;

    order.totalCost -= order.orderedOptions[deleteChoice - 1].getPrice();
    order.orderedOptions.erase(order.orderedOptions.begin() + deleteChoice - 1);
}