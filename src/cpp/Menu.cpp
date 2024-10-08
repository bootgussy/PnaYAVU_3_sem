#include "Menu.h"

using namespace std;

Menu::Menu()
{
    addCategory("Drinks");
    addCategory("Desserts");

    addOptionToCategory("Drinks", "Cappuccino", 5.5);
    addOptionToCategory("Drinks", "Latte", 6.0);
    addOptionToCategory("Desserts", "Cheesecake", 4.5);
    addOptionToCategory("Desserts", "Tiramisu", 5.0);
}

void Menu::addCategory(const string& categoryName)
{
    categories.push_back(new Category(categoryName));
}

void Menu::addOptionToCategory(const string& categoryName, const string& optionName, double price) const
{
    for (auto& category : categories)
    {
        if (category->name == categoryName)
        {
            category->addOption(optionName, price);
            return;
        }
    }
    cout << "Category not found: " << categoryName << endl;
}

void Menu::displayMenu() const
{
    cout << "Menu:\n";
    for (int i = 0; i < categories.size(); ++i)
    {
        cout << i + 1 << ". " << categories[i]->name << "\n";
    }
}

void Menu::selectOption()
{
    displayMenu();

    int categoryChoice;
    cout << "Select category (enter number): ";
    cin >> categoryChoice;

    if (categoryChoice > 0 && categoryChoice <= categories.size())
    {
        Category const* const selectedCategory = categories[categoryChoice - 1];
        selectedCategory->displayOptions();

        int optionChoice;
        cout << "Select option (enter number): ";
        cin >> optionChoice;

        MenuOption* selectedOption = selectedCategory->getOption(optionChoice - 1);
        if (selectedOption)
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

void Menu::finishOrder() const
{
    cout << "Your order:\n";
    for (const auto& option : order.orderedOptions)
    {
        cout << "- " << option->GetName() << " : $" << option->GetPrice() << '\n';
    }
    cout << "Total: $" << order.totalCost << '\n';
}

void Menu::deleteOption()
{
    int deleteChoice;
    int optionNumber = 0;

    cout << "Your order:\n";
    for (const auto& option : order.orderedOptions)
    {
        ++optionNumber;
        cout << optionNumber << ". " << option->GetName() << " : $" << option->GetPrice() << '\n';
    }

    cout << "Select the option to remove:\n";
    cin >> deleteChoice;

    while (deleteChoice < 1 || deleteChoice > order.orderedOptions.size())
    {
        cout << "Error. Please enter a valid option number:\n";
        cin >> deleteChoice;
    }

    cout << endl;

    order.totalCost -= order.orderedOptions[deleteChoice - 1]->GetPrice();
    order.orderedOptions.erase(order.orderedOptions.begin() + deleteChoice - 1);
}
