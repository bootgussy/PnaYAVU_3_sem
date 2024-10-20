#include <string>
#include <iostream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include "../header/Manager.h"
#include "../header/Database.h"
#include "../header/Menu.h"
#include "../header/MenuOption.h"
#include "../header/Order.h"

Manager::Manager() = default;

std::string Manager::getRole() const {
    return "Manager";
}

void Manager::changePrice() const
{
    Menu menu;
    MenuOption currentOption;
    std::string name;
    double newPrice;

    currentOption = menu.selectOption();
    name = currentOption.getName();
    if (currentOption != MenuOption())
    {
        std::cout << "Current price for " << name << ": " << currentOption.getPrice() << std::endl;
        std::cout << "New price for " << name << ": ";
        std::cin >> newPrice;

        while (newPrice <= 0)
        {
            std::cout << "Please write correct price" << std::endl;
            std::cin >> newPrice;
        }

        Database::getInstance()->setPrice(name, newPrice);

        std::cout << "Price changed successfully!" << std::endl;
    }
}

void Manager::addDiscounts() const
{
    Menu menu;
    MenuOption currentOption;
    std::string name;
    double newDiscount;

    currentOption = menu.selectOption();
    name = currentOption.getName();
    
    if (currentOption != MenuOption())
    {
        std::cout << "Current discount for " << name << ": " << currentOption.getDiscount() << "%" << std::endl;
        std::cout << "New discount (%) for " << name << ": ";
        std::cin >> newDiscount;

        while (newDiscount <= 0 || newDiscount >= 100)
        {
            std::cout << "Please write correct discount (%): ";
            std::cin >> newDiscount;
        }

        Database::getInstance()->setDiscount(name, newDiscount);

        std::cout << "Discount changed successfully!" << std::endl;
    }
}

void Manager::removeDiscounts() const
{
    Menu menu;
    MenuOption currentOption;
    std::string name;

    currentOption = menu.selectOption();
    name = currentOption.getName();
    
    if (currentOption != MenuOption())
    {
        Database::getInstance()->setDiscount(name, 0);
        std::cout << "Discount removed successfully!" << std::endl;
    }
}

void Manager::addCombo() const
{
    Menu menu;
    Order order;
    char continueOrdering;
    char needDeleteOption;
    std::string comboName;
    double totalCost = 0.0;

    do
    {
        MenuOption currentOption;

        order = menu.addToOrder(order);

        std::cout << "Do you want to add more options? (y/n): ";
        std::cin >> continueOrdering;

        while (continueOrdering != 'y' && continueOrdering != 'n')
        {
            std::cout << "Choose yes or no (y/n): ";
            std::cin >> continueOrdering;
        }

        std::cout << '\n';

    } while (continueOrdering != 'n');

    do
    {
        std::cout << "Do you want to delete any option? (y/n): ";
        std::cin >> needDeleteOption;

        while (needDeleteOption != 'y' && needDeleteOption != 'n')
        {
            std::cout << "Choose yes or no (y/n): ";
            std::cin >> needDeleteOption;
        }

        if (needDeleteOption == 'y')
        {
            order = menu.deleteOption(order);
        }
    } while (needDeleteOption != 'n');

    std::cout << std::endl;

    for (const auto& option : order.orderedOptions)
    {
        totalCost += option.getPrice() - option.getPrice() / 100.0 * option.getDiscount();
        if (option.getDiscount() == 0)
        {
            std::cout << "- " << option.getName() << " : $" << option.getPrice() << '\n';
        }
        else
        {
            std::cout << "- " << option.getName() << " : $" << option.getPrice() / 100.0 * (100 - option.getDiscount()) << " (Discount " << option.getDiscount() << "%)" << '\n';
        }
    }

    std::cout << std::endl;

    std::cout << "Enter name of combo: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, comboName);

    Database::getInstance()->addCombo(comboName, order, round(totalCost));
}

void Manager::addCategoryToMenu() const
{
    std::string categoryName;
    char needAddCategory;

    std::cout << "Write category name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, categoryName);

    std::cout << "Are you sure you want to add category to menu? (y/n): ";
    std::cin >> needAddCategory;
    while (needAddCategory != 'y' && needAddCategory != 'n')
    {
        std::cout << "Choose yes or no (y/n): ";
        std::cin >> needAddCategory;
    }

    if (needAddCategory == 'y')
    {
        if (Database::getInstance()->addCategory(categoryName))
        {
            std::cout << "Category added to menu succesfully!" << std::endl;
        }
        else
        {
            std::cout << "Ñategory is already in menu" << std::endl;
        }
    }
    else
    {
        std::cout << "Adding was canceled" << std::endl;
    }

    
}

void Manager::addOptionToCategory() const
{
    Menu menu;
    std::string optionName;
    int optionPrice;
    char needAddOption;

    menu.displayMenu();

    int categoryChoice;
    std::cout << "Select category (enter number): ";
    std::cin >> categoryChoice;

    if (categoryChoice > 0 && categoryChoice <= Database::getInstance()->categoriesSize())
    {
        std::cout << "Enter name of option: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, optionName);
        std::cout << "Enter price of option: ";
        std::cin >> optionPrice;

        std::cout << "Are you sure you want to add option to category " << Database::getInstance()->getCategory(categoryChoice) << "? (y/n): ";
        std::cin >> needAddOption;
        while (needAddOption != 'y' && needAddOption != 'n')
        {
            std::cout << "Choose yes or no (y/n): ";
            std::cin >> needAddOption;
        }

        if (needAddOption == 'y')
        {
            if (Database::getInstance()->addOptionToCategory(Database::getInstance()->getCategory(categoryChoice), optionName, optionPrice, 0))
            {
                std::cout << "Option " << optionName << " succesfully added to category " << Database::getInstance()->getCategory(categoryChoice) << "!" << std::endl;
            }
            else
            {
                std::cout << "Option " << optionName << " is already in category " << Database::getInstance()->getCategory(categoryChoice) << std::endl;
            }
        }
        else
        {
            std::cout << "Adding was canceled" << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid category selection!" << std::endl;
    }
}

void Manager::removeOptionFromMenu() const
{
    Menu menu;
    MenuOption currentOption;
    char needDeleteOption;
    std::string name;

    std::cout << "Choose option to remove:" << std::endl;

    currentOption = menu.selectOption();
    name = currentOption.getName();

    if (currentOption != MenuOption())
    {
        std::cout << "Are you sure you want to remove option from menu? (y/n): ";
        std::cin >> needDeleteOption;
        while (needDeleteOption != 'y' && needDeleteOption != 'n')
        {
            std::cout << "Choose yes or no (y/n): ";
            std::cin >> needDeleteOption;
        }

        if (needDeleteOption == 'y')
        {
            Database::getInstance()->deleteOption(name);
            std::cout << "Option " << name << " succesfully removed from menu!" << std::endl;
        }
        else
        {
            std::cout << "Removing was canceled" << std::endl;
        }
    }
}