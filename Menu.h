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