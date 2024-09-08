#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MenuSystem {
public:
    struct MenuItem {
        string name;
        double price;

        MenuItem(const string& itemName, double itemPrice) : name(itemName), price(itemPrice) {}
    };

    MenuSystem();
    void addCategory(const string& categoryName);
    void addMenuItemToCategory(const string& categoryName, const string& itemName, double price) const;
    void displayMenu() const;
    void selectItem();
    void finishOrder() const;

private:
    class Category {
    public:
        string name;
        vector<MenuItem*> items;

        Category(const string& categoryName);
        void addItem(const string& itemName, double itemPrice);
        void displayItems() const;
        MenuItem* getItem(size_t index) const;
    };

    class Order {
    public:
        vector<MenuItem*> orderedItems;
        double totalCost = 0.0;

        void addItem(MenuItem* item);
    };

    vector<Category*> categories;
    Order order;
};

#endif
