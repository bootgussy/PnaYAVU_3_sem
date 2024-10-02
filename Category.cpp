#include "Category.h"
#include <iostream>

using namespace std;

Category::Category(const string& categoryName) : name(categoryName) {}

void Category::addOption(const string& optionName, double optionPrice)
{
    options.push_back(new MenuOption(optionName, optionPrice));
}

void Category::displayOptions() const
{
    cout << "Category: " << name << "\n";
    for (int i = 0; i < options.size(); ++i)
    {
        cout << i + 1 << ". " << options[i]->GetName() << " - $" << options[i]->GetPrice() << '\n';
    }
}

MenuOption* Category::getOption(int index) const
{
    if (index < options.size())
    {
        return options[index];
    }
    return nullptr;
}
