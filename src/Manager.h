#pragma once

#include "sqlite3.h"
#include "Database.h"
#include "Person.h"

class Manager : public Person
{
private:
    sqlite3* database = Database::getInstance()->getDatabase();
    sqlite3_stmt* stmt;

public:
    Manager();

    std::string getRole() const override;

    void changePrice(const std::string &name, double newPrice) const;
    void changeDiscount(const std::string &name, int newDiscount) const;
    void addCombo() const;
    void addCategoryToMenu() const;
    void addOptionToCategory() const;
    void removeCategoryFromMenu() const;
    void removeOptionFromMenu() const;
};
