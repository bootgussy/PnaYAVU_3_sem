#include "MenuSystem.h"

using namespace std;

MenuSystem::MenuItem::MenuItem(const string& itemName, double itemPrice)
{
    name = itemName;
    price = itemPrice;
}

MenuSystem::MenuSystem() {
    addCategory("Drinks");
    addCategory("Desserts");

    addMenuItemToCategory("Drinks", "Cappuccino", 3.5);
    addMenuItemToCategory("Drinks", "Latte", 4.0);
    addMenuItemToCategory("Desserts", "Cheesecake", 4.5);
    addMenuItemToCategory("Desserts", "Chocolate Cake", 5.0);
}

void MenuSystem::addCategory(const string& categoryName) {
    categories.push_back(new Category(categoryName));
}

void MenuSystem::addMenuItemToCategory(const string& categoryName, const string& itemName, double price) {
    for (auto& category : categories) {
        if (category->name == categoryName) {
            category->addItem(itemName, price);
            return;
        }
    }
    cout << "Category not found: " << categoryName << endl;
}

void MenuSystem::displayMenu() const {
    cout << "Menu:\n";
    for (size_t i = 0; i < categories.size(); ++i) {
        cout << i + 1 << ". " << categories[i]->name << "\n";
    }
}

void MenuSystem::selectItem() {
    displayMenu();
    int categoryChoice;
    cout << "Select category (enter number): ";
    cin >> categoryChoice;

    if (categoryChoice > 0 && static_cast<size_t>(categoryChoice) <= categories.size()) {
        Category* selectedCategory = categories[categoryChoice - 1];
        selectedCategory->displayItems();
        int itemChoice;
        cout << "Select item (enter number): ";
        cin >> itemChoice;

        MenuItem* selectedItem = selectedCategory->getItem(itemChoice - 1);
        if (selectedItem) {
            order.addItem(selectedItem);
        }
        else {
            cout << "Invalid item selection!\n";
        }
    }
    else {
        cout << "Invalid category selection!\n";
    }
}

void MenuSystem::finishOrder() const {
    cout << "Your order:\n";
    for (const auto& item : order.orderedItems) {
        cout << "- " << item->name << " : $" << item->price << '\n';
    }
    cout << "Total: $" << order.totalCost << '\n';
}

MenuSystem::~MenuSystem() {
    for (auto category : categories) {
        delete category;
    }
}

MenuSystem::Category::Category(const string& categoryName) : name(categoryName) {}

void MenuSystem::Category::addItem(const string& itemName, double itemPrice) {
    items.push_back(new MenuItem(itemName, itemPrice));
}

void MenuSystem::Category::displayItems() const {
    cout << "Category: " << name << "\n";
    for (size_t i = 0; i < items.size(); ++i) {
        cout << i + 1 << ". " << items[i]->name << " - $" << items[i]->price << '\n';
    }
}

MenuSystem::MenuItem* MenuSystem::Category::getItem(size_t index) const {
    if (index < items.size()) {
        return items[index];
    }
    return nullptr;
}

MenuSystem::Category::~Category() {
    for (auto item : items) {
        delete item;
    }
}

void MenuSystem::Order::addItem(MenuItem* item) {
    if (item) {
        orderedItems.push_back(item);
        totalCost += item->price;
    }
}
