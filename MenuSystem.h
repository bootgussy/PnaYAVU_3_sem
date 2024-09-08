#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include <iostream>
#include <string>
#include <vector>

class MenuSystem {
public:
    struct MenuItem {
        std::string name;
        double price;

        MenuItem(const std::string& itemName, double itemPrice) : name(itemName), price(itemPrice) {}
    };

    MenuSystem();
    void addCategory(const std::string& categoryName);
    void addMenuItemToCategory(const std::string& categoryName, const std::string& itemName, double price) const;
    void displayMenu() const;
    void selectItem();
    void finishOrder() const;

private:
    class Category {
    public:
        std::string name;
        std::vector<MenuItem*> items;

        Category(const std::string& categoryName);
        void addItem(const std::string& itemName, double itemPrice);
        void displayItems() const;
        MenuItem* getItem(size_t index) const;
    };

    class Order {
    public:
        std::vector<MenuItem*> orderedItems;
        double totalCost = 0.0;

        void addItem(MenuItem* item);
    };

    std::vector<Category*> categories;
    Order order;
};

#endif
