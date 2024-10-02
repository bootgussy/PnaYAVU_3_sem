<<<<<<< HEAD:Menu.h
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Category.h"
#include "Order.h"

class Menu
{
public:
    Menu();

    void addCategory(const std::string& categoryName);
    void addOptionToCategory(const std::string& categoryName, const std::string& optionName, double price) const;
    void displayMenu() const;
    void selectOption();
    void finishOrder() const;
    void deleteOption();

private:
    std::vector<Category*> categories;
    Order order;
};
=======
#pragma once

#include <iostream>
#include <string>
#include <vector>

class Menu
{
public:
    class MenuOption
    {
        std::string name;
        double price;

    public:
        MenuOption(const std::string& optionName, double optionPrice) : name(optionName), price(optionPrice) {}

        std::string GetName() const
        {
            return name;
        }

        double GetPrice() const
        {
            return price;
        }
    };

    Menu();

    void addCategory(const std::string& categoryName);
    void addOptionToCategory(const std::string& categoryName, const std::string& optionName, double price) const;
    void displayMenu() const;
    void selectOption();
    void finishOrder() const;
    void deleteOption();

private:
    class Category
    {
    public:
        std::string name;
        std::vector<MenuOption*> options;

        explicit Category(const std::string& categoryName);
        void addOption(const std::string& optionName, double optionPrice);
        void displayOptions() const;
        MenuOption* getOption(int index) const;
    };

    class Order
    {
    public:
        std::vector<MenuOption*> orderedOptions;
        double totalCost = 0.0;

        void addOption(MenuOption* item);
    };

    std::vector<Category*> categories;
    Order order;
};
>>>>>>> 1d8c228f0c910e9fe5c0ddc10ccd48f3ab473035:src/Menu.h
